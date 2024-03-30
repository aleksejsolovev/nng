# Summary

- [Chapter 1](./chapter_1.md)

- [Overview](./overview/index.md)

  - [RAW mode](./overview/raw.md)

- [Protocols](proto/index.md)

  - [BUS](proto/bus.md)
  - [PAIR](proto/pair.md)
  - [PUB](proto/pub.md)
  - [PULL](proto/pull.md)
  - [PUSH](proto/push.md)
  - [REP](proto/rep.md)
  - [REQ](proto/req.md)
  - [RESPONDENT](proto/respondent.md)
  - [SUB](proto/sub.md)
  - [SURVEYOR](proto/surveyor.md)

- [Transports](tran/index.md)

  - [INPROC](tran/inproc.md)
  - [TCP](tran/tcp.md)

- [API Reference](./api/index.md)

  - [Messages](msg/index.md)

    - [nng_msg_alloc](msg/nng_msg_alloc.md)
    - [nng_msg_append](msg/nng_msg_append.md)
    - [nng_msg_body](msg/nng_msg_body.md)
    - [nng_msg_capacity](msg/nng_msg_capacity.md)
    - [nng_msg_chop](msg/nng_msg_chop.md)
    - [nng_msg_clear](msg/nng_msg_clear.md)
    - [nng_msg_dup](msg/nng_msg_dup.md)
    - [nng_msg_free](msg/nng_msg_free.md)
    - [nng_msg_get_pipe](msg/nng_msg_get_pipe.md)
    - [nng_msg_header](msg/nng_msg_header.md)
    - [nng_msg_header_append](msg/nng_msg_header_append.md)
    - [nng_msg_header_chop](msg/nng_msg_header_chop.md)
    - [nng_msg_header_clear](msg/nng_msg_header_clear.md)
    - [nng_msg_header_insert](msg/nng_msg_header_insert.md)
    - [nng_msg_header_len](msg/nng_msg_header_len.md)
    - [nng_msg_header_trim](msg/nng_msg_header_trim.md)
    - [nng_msg_insert](msg/nng_msg_insert.md)
    - [nng_msg_len](msg/nng_msg_len.md)
    - [nng_msg_realloc](msg/nng_msg_realloc.md)
    - [nng_msg_reserve](msg/nng_msg_reserve.md)
    - [nng_msg_set_pipe](msg/nng_msg_set_pipe.md)
    - [nng_msg_trim](msg/nng_msg_trim.md)

  - [Sockets](api/socket/index.md)

    - [nng_bus_open](api/socket/nng_bus_open.md)
    - [nng_close](api/socket/nng_close.md)
    - [nng_pub_open](api/socket/nng_pub_open.md)

  - [Contexts](api/context/index.md)

    - [nng_ctx_close](ctx/nng_ctx_close.md)
    - [nng_ctx_get](ctx/nng_ctx_get.md)
    - [nng_ctx_getopt](ctx/nng_ctx_getopt.md)
    - [nng_ctx_id](ctx/nng_ctx_id.md)
    - [nng_ctx_open](ctx/nng_ctx_open.md)
    - [nng_ctx_recv](ctx/nng_ctx_recv.md)
    - [nng_ctx_recvmsg](ctx/nng_ctx_recvmsg.md)
    - [nng_ctx_send](ctx/nng_ctx_send.md)
    - [nng_ctx_sendmsg](ctx/nng_ctx_sendmsg.md)
    - [nng_ctx_set](ctx/nng_ctx_set.md)
    - [nng_ctx_setopt](ctx/nng_ctx_setopt.md)

  - [Asynchronous I/O](./api/aio/index.md)

    - [nng_aio_abort](api/aio/nng_aio_abort.md)
    - [nng_aio_alloc](api/aio/nng_aio_alloc.md)
    - [nng_aio_busy](api/aio/nng_aio_busy.md)
    - [nng_aio_cancel](api/aio/nng_aio_cancel.md)
    - [nng_aio_count](api/aio/nng_aio_count.md)
    - [nng_aio_free](api/aio/nng_aio_free.md)
    - [nng_aio_get_msg](api/aio/nng_aio_get_msg.md)
    - [nng_aio_get_output](api/aio/nng_aio_get_output.md)
    - [nng_aio_result](api/aio/nng_aio_result.md)
    - [nng_aio_set_input](api/aio/nng_aio_set_input.md)
    - [nng_aio_set_iov](api/aio/nng_aio_set_iov.md)
    - [nng_aio_set_msg](api/aio/nng_aio_set_msg.md)
    - [nng_aio_set_timeout](api/aio/nng_aio_set_timeout.md)
    - [nng_aio_stop](api/aio/nng_aio_stop.md)
    - [nng_aio_wait](api/aio/nng_aio_wait.md)

  - [Asynchronous I/O for Providers](api/aio_provider/index.md)

    - [nng_aio_begin](api/aio_provider/nng_aio_begin.md)
    - [nng_aio_defer](api/aio_provider/nng_aio_defer.md)
    - [nng_aio_finish](api/aio_provider/nng_aio_finish.md)
    - [nng_aio_get_input](api/aio_provider/nng_aio_get_input.md)
    - [nng_aio_set_output](api/aio_provider/nng_aio_set_output.md)

  - [Utility Functions](api/util/index.md)

    - [nng_alloc](util/nng_alloc.md)
    - [nng_clock](util/nng_clock.md)
    - [nng_free](util/nng_free.md)
    - [nng_msleep](util/nng_msleep.md)
    - [nng_random](util/nng_random.md)
    - [nng_sleep_aio](util/nng_sleep_aio.md)
    - [nng_strdup](util/nng_strdup.md)
    - [nng_strerror](util/nng_strerror.md)
    - [nng_strfree](util/nng_strfree.md)
    - [nng_version](util/nng_version.md)

  - [Threads and Synchronization](thr/index.md)

    - [nng_cv_alloc](thr/nng_cv_alloc.md)
    - [nng_cv_free](thr/nng_cv_free.md)
    - [nng_cv_until](thr/nng_cv_until.md)
    - [nng_cv_wait](thr/nng_cv_wait.md)
    - [nng_cv_wake](thr/nng_cv_wake.md)
    - [nng_cv_wake1](thr/nng_cv_wake1.md)
    - [nng_mtx_alloc](thr/nng_mtx_alloc.md)
    - [nng_mtx_free](thr/nng_mtx_free.md)
    - [nng_mtx_lock](thr/nng_mtx_lock.md)
    - [nng_mtx_unlock](thr/nng_mtx_unlock.md)

  - [Legacy Compatibility](api/compat/index.md)

- [Index](./indexing.md)