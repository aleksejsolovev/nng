//
// Copyright 2024 Staysail Systems, Inc. <info@staysail.tech>
// Copyright 2018 Capitar IT Group BV <info@capitar.com>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#include "core/nng_impl.h"
#include "core/platform.h"

#include <nuts.h>

#ifdef NNG_ENABLE_IPV6
uint8_t v6loop[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

static bool
has_v6(void)
{
	nng_sockaddr  sa;
	nni_plat_udp *u;
	int           rv;

	sa.s_in6.sa_family = NNG_AF_INET6;
	sa.s_in6.sa_port   = 0;
	memcpy(sa.s_in6.sa_addr, v6loop, 16);

	rv = nni_plat_udp_open(&u, &sa);
	if (rv == 0) {
		nni_plat_udp_close(u);
	}
	return (rv == 0);
}
#endif

void
test_google_dns(void)
{
	nng_aio        *aio;
	nng_sockaddr    sa;
	nni_resolv_item item = { 0 };

	item.ri_host    = "google-public-dns-a.google.com";
	item.ri_port    = 80;
	item.ri_passive = true;
	item.ri_sa      = &sa;
	item.ri_family  = NNG_AF_INET;

	NUTS_PASS(nng_aio_alloc(&aio, NULL, NULL));
	nni_resolv(&item, aio);
	nng_aio_wait(aio);
	NUTS_PASS(nng_aio_result(aio));
	NUTS_TRUE(sa.s_in.sa_family == NNG_AF_INET);
	NUTS_TRUE(sa.s_in.sa_port == nuts_be16(80));
	NUTS_TRUE(sa.s_in.sa_addr == 0x08080808); // aka 8.8.8.8
	nng_aio_free(aio);
}

void
test_hostname_too_long(void)
{
	nng_aio        *aio;
	nng_sockaddr    sa;
	char            buffer[512];
	nni_resolv_item item = { 0 };

	memset(buffer, 'a', sizeof(buffer) - 1);
	buffer[sizeof(buffer) - 1] = '\0';
	NUTS_PASS(nng_aio_alloc(&aio, NULL, NULL));
	item.ri_family  = NNG_AF_INET;
	item.ri_passive = true;
	item.ri_host    = buffer;
	item.ri_port    = 80;
	item.ri_sa      = &sa;
	nni_resolv(&item, aio);
	nng_aio_wait(aio);
	NUTS_FAIL(nng_aio_result(aio), NNG_EADDRINVAL);
	nng_aio_free(aio);
}

void
test_numeric_addr(void)
{
	nng_aio        *aio;
	nng_sockaddr    sa;
	nni_resolv_item item = { 0 };

	NUTS_PASS(nng_aio_alloc(&aio, NULL, NULL));
	item.ri_family  = NNG_AF_INET;
	item.ri_host    = "8.8.4.4";
	item.ri_port    = 69;
	item.ri_passive = true;
	item.ri_sa      = &sa;
	nni_resolv(&item, aio);
	nng_aio_wait(aio);
	NUTS_PASS(nng_aio_result(aio));
	NUTS_TRUE(sa.s_in.sa_family == NNG_AF_INET);
	NUTS_TRUE(sa.s_in.sa_port == nuts_be16(69));
	NUTS_TRUE(sa.s_in.sa_addr == nuts_be32(0x08080404)); // 8.8.4.4.
	nng_aio_free(aio);
}

#ifdef NNG_ENABLE_IPV6
void
test_numeric_v6(void)
{
	nng_aio        *aio;
	nng_sockaddr    sa;
	nni_resolv_item item = { 0 };

	if (!has_v6()) {
		return;
	}
	NUTS_MSG("IPV6 support present");
	NUTS_PASS(nng_aio_alloc(&aio, NULL, NULL));
	item.ri_family  = NNG_AF_INET6;
	item.ri_host    = "::1";
	item.ri_port    = 80;
	item.ri_passive = true;
	item.ri_sa      = &sa;
	nni_resolv(&item, aio);
	nng_aio_wait(aio);
	NUTS_PASS(nng_aio_result(aio));
	NUTS_TRUE(sa.s_in6.sa_family == NNG_AF_INET6);
	NUTS_TRUE(sa.s_in6.sa_port == nuts_be16(80));
	NUTS_TRUE(memcmp(sa.s_in6.sa_addr, v6loop, 16) == 0);
	nng_aio_free(aio);
}
#endif

void
test_service_names(void)
{
	nng_aio        *aio;
	nng_sockaddr    sa;
	uint32_t        port;
	nni_resolv_item item = { 0 };

	NUTS_PASS(nng_aio_alloc(&aio, NULL, NULL));
	item.ri_family  = NNG_AF_INET;
	item.ri_host    = "8.8.4.4";
	item.ri_port    = 80;
	item.ri_passive = true;
	item.ri_sa      = &sa;
	nni_resolv(&item, aio);
	nng_aio_wait(aio);
	NUTS_PASS(nng_aio_result(aio));
	NUTS_TRUE(sa.s_in.sa_port == nuts_be16(80));
	NUTS_TRUE(sa.s_in.sa_addr = nuts_be32(0x08080404));
	nng_aio_free(aio);

	NUTS_PASS(nni_get_port_by_name("http", &port));
	NUTS_TRUE(port == 80);

	NUTS_PASS(nni_get_port_by_name("25", &port));
	NUTS_TRUE(port == 25);
}

void
test_localhost_v4(void)
{
	nng_aio        *aio;
	nng_sockaddr    sa;
	nni_resolv_item item = { 0 };

	NUTS_PASS(nng_aio_alloc(&aio, NULL, NULL));
	item.ri_family  = NNG_AF_INET;
	item.ri_host    = "localhost";
	item.ri_port    = 80;
	item.ri_passive = true;
	item.ri_sa      = &sa;
	nni_resolv(&item, aio);
	nng_aio_wait(aio);
	NUTS_PASS(nng_aio_result(aio));
	NUTS_TRUE(sa.s_in.sa_family == NNG_AF_INET);
	NUTS_TRUE(sa.s_in.sa_port == nuts_be16(80));
	NUTS_TRUE(sa.s_in.sa_addr == nuts_be32(0x7f000001));
	nng_aio_free(aio);
}

void
test_localhost_unspecified(void)
{
	nng_aio        *aio;
	nng_sockaddr    sa;
	nni_resolv_item item = { 0 };

	NUTS_PASS(nng_aio_alloc(&aio, NULL, NULL));
	item.ri_family  = NNG_AF_UNSPEC;
	item.ri_host    = "localhost";
	item.ri_port    = 80;
	item.ri_passive = true;
	item.ri_sa      = &sa;
	nni_resolv(&item, aio);
	nng_aio_wait(aio);
	NUTS_PASS(nng_aio_result(aio));
	NUTS_TRUE(
	    (sa.s_family == NNG_AF_INET) || (sa.s_family == NNG_AF_INET6));
	switch (sa.s_family) {
	case NNG_AF_INET:
		NUTS_TRUE(sa.s_in.sa_port == nuts_be16(80));
		NUTS_TRUE(sa.s_in.sa_addr == nuts_be32(0x7f000001));
		break;
#ifdef NNG_ENABLE_IPV6
	case NNG_AF_INET6:
		NUTS_TRUE(sa.s_in6.sa_port == nuts_be16(80));
		NUTS_TRUE(memcmp(sa.s_in6.sa_addr, v6loop, 16) == 0);
		break;
#endif
	}
	nng_aio_free(aio);
}

void
test_null_passive(void)
{
	nng_aio        *aio;
	nng_sockaddr    sa;
	nni_resolv_item item = { 0 };

	NUTS_PASS(nng_aio_alloc(&aio, NULL, NULL));
	item.ri_family  = NNG_AF_INET;
	item.ri_host    = NULL;
	item.ri_port    = 80;
	item.ri_passive = true;
	item.ri_sa      = &sa;
	nni_resolv(&item, aio);
	nng_aio_wait(aio);
	NUTS_PASS(nng_aio_result(aio));
	NUTS_TRUE(sa.s_in.sa_family == NNG_AF_INET);
	NUTS_TRUE(sa.s_in.sa_port == nuts_be16(80));
	NUTS_TRUE(sa.s_in.sa_addr == 0); // any local address
	nng_aio_free(aio);
}

void
test_null_not_passive(void)
{
	nng_aio        *aio;
	nng_sockaddr    sa;
	nni_resolv_item item = { 0 };

	NUTS_PASS(nng_aio_alloc(&aio, NULL, NULL));
	item.ri_family  = NNG_AF_INET;
	item.ri_host    = NULL;
	item.ri_port    = 80;
	item.ri_passive = false;
	item.ri_sa      = &sa;
	nni_resolv(&item, aio);
	nng_aio_wait(aio);
	// We can either get invalid address, or a loopback address.
	// Most systems do the former, but Linux does the latter.
	if (nng_aio_result(aio) == 0) {
		NUTS_TRUE(sa.s_family == NNG_AF_INET);
		NUTS_TRUE(sa.s_in.sa_addr == nuts_be32(0x7f000001));
		NUTS_TRUE(sa.s_in.sa_port == nuts_be16(80));
	} else {
		NUTS_FAIL(nng_aio_result(aio), NNG_EADDRINVAL);
	}
	nng_aio_free(aio);
}

void
test_bad_family(void)
{
	nng_aio        *aio;
	nng_sockaddr    sa;
	nni_resolv_item item = { 0 };

	NUTS_PASS(nng_aio_alloc(&aio, NULL, NULL));
	item.ri_family  = NNG_AF_INPROC;
	item.ri_host    = "/abcdef";
	item.ri_port    = 80;
	item.ri_passive = false;
	item.ri_sa      = &sa;
	nni_resolv(&item, aio);
	nng_aio_wait(aio);
	NUTS_FAIL(nng_aio_result(aio), NNG_ENOTSUP);
	nng_aio_free(aio);
}

void
test_aio_stopped(void)
{
	nng_aio        *aio;
	nng_sockaddr    sa;
	nni_resolv_item item = { 0 };

	NUTS_PASS(nng_aio_alloc(&aio, NULL, NULL));
	item.ri_family  = NNG_AF_INPROC;
	item.ri_host    = "/abcdef";
	item.ri_port    = 80;
	item.ri_passive = false;
	item.ri_sa      = &sa;
	nng_aio_stop(aio);
	nni_resolv(&item, aio);
	nng_aio_wait(aio);
	NUTS_FAIL(nng_aio_result(aio), NNG_ESTOPPED);
	nng_aio_free(aio);
}

NUTS_TESTS = {
	{ "resolve google dns", test_google_dns },
	{ "resolve hostname too long", test_hostname_too_long },
	{ "resolve numeric addr", test_numeric_addr },
#ifdef NNG_ENABLE_IPV6
	{ "resolve numeric v6", test_numeric_v6 },
#endif
	{ "resolve service names", test_service_names },
	{ "resolve localhost v4", test_localhost_v4 },
	{ "resolve localhost unspecified", test_localhost_unspecified },
	{ "resolve null passive", test_null_passive },
	{ "resolve null not passive", test_null_not_passive },
	{ "resolve bad family", test_bad_family },
	{ "resolve aio stopped", test_bad_family },
	{ NULL, NULL },
};
