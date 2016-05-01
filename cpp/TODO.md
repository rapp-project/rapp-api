[TODO changes for 0.6.0]

# API

https://github.com/rapp-project/rapp-platform/tree/web_services_doc/rapp_web_services/services

# Implement new services

1. email_fetch
2. email_send
3. weather_report_current
4. weather_report_forecast
5. geolocation
6. news_explore

# Merge / Refactor asio_handling

1. Add a common/base class for most common handling (asio_handler)
2. Refactor and fuse all handling there (in a .cpp) not header
3. use asio_socket to add a virtual get_socket() method
4. asio_service_http => asio_http, asio_socket_https => asio_https
5. each one should implement `schedule` and the specifics (e.g., handshakes, etc)

# Add a Timer
1. Add a Timer/Time-out to all asio classes!
   see: http://www.boost.org/doc/libs/1_45_0/doc/html/boost_asio/example/timeouts/async_tcp_client.cpp
   current timer implementation is WRONG

# Examples
1. add `examples/cognitive_example`
2. add `examples/email_example`

# Tests
1. add new unit tests (for new object class `human`)
2. Try to induce time-outs, DDoS and other problematic issues
