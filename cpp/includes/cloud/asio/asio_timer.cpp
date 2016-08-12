#include "asio_timer.hpp"
namespace rapp {
namespace cloud {

asio_timer::asio_timer(std::function<void()> callback) 
: callback_(callback), io_time_()
{
	assert(callback_);
	timer_ = std::make_unique<boost::asio::deadline_timer>(io_time_);
	assert(timer_);
} 

void asio_timer::set_timeout(unsigned int arg)
{
	timer_->expires_from_now(boost::posix_time::seconds(arg));
	timer_->async_wait(boost::bind(&timer::check_timeout, this));
}

void asio_timer::check_timeout() const 
{
	// timer has expired - call the callback
	if (timer_->expires_at() <= boost::asio::deadline_timer::traits_type::now()) {
		callback_();
		reset();
	}
	// Put the actor back to sleep.
	else {
		timer_->async_wait(boost::bind(&timer::check_timeout, this));
	}
}

void asio_timer::reset()
{
	timer_->expires_at(boost::posix_time::pos_infin);
	io_time_.stop();
}

}
}
