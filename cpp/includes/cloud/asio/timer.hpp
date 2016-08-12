#ifndef RAPP_ASIO_TIMER
#define RAPP_ASIO_TIMER
#include "includes.ihh"
namespace rapp{
namespace cloud {

/**
 * \class asio_response
 * \version 0.7.0
 * \date August 2016 
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 *
 */

class timer
{
public:

    /// \brief construct using \param error_handler which will receive time-outs
    timer()
    : io_time_()
    {
        timer_ = std::make_unique<boost::asio::deadline_timer>(io_time_);
        timer_->async_wait(boost::bind(&timer::check_timeout, this));
        assert(timer_);
    } 

    /// \brief set the timer with \param seconds
    void set_timeout(unsigned int arg)
    {
        assert(timer_);
        timer_->expires_from_now(boost::posix_time::seconds(arg));
    }

    /// \brief
    /// \note if timed-out, callback `error_handler` will receive an error
    bool check_timeout() const 
    {
        assert(timer_ && callback_);
        // timer has expired
        if (timer_->expires_at() <= boost::asio::deadline_timer::traits_type::now()) {
            return true;
        }
	    else {
		    // Put the actor back to sleep.
		    timer_->async_wait(boost::bind(&timer::check_timeout, this));
            return false;
	    }
    }

    /// \brief reset the timer
    void reset()
    {
        assert(timer_);
        timer_->expires_at(boost::posix_time::pos_infin);
	    io_time_.stop();
    }

private:

    /// Time-out timer
    std::unique_ptr<boost::asio::deadline_timer> timer_;
    /// Time-out service
    boost::asio::io_service io_time_;
};
}
}
#endif
