
#include <iq/timer.hpp>

namespace iq
{
	const unsigned int timer::HOURS_PER_DAY = 24;
	const unsigned int timer::MINS_PER_HOUR = 60;
	const unsigned int timer::SECS_PER_MIN = 60;
	const unsigned int timer::SECS_PER_HOUR = 60 * 60;
	const unsigned int timer::SECS_PER_DAY = (60 * 60) * 24;
	
	timer::timer(void)
	{
		this->running = false;
		this->ticks = 0;
	
		install_param_int_ex(timer::tick, this, BPS_TO_TIMER(1));
	}
	
	timer::~timer(void)
	{
	}
	
	unsigned int timer::after_days(const unsigned int total_secs)
	{
		return(total_secs - (timer::days(total_secs) * timer::SECS_PER_DAY));
	}
	
	unsigned int timer::after_hours(const unsigned int total_secs)
	{
		return(timer::after_days(total_secs) - (timer::hours(total_secs) * timer::SECS_PER_HOUR));
	}
	
	unsigned int timer::after_mins(const unsigned int total_secs)
	{
		return(timer::after_hours(total_secs) - (timer::mins(total_secs) * timer::SECS_PER_MIN));
	}
	
	unsigned int timer::days(void) const
	{
		return(timer::days(this->total_secs()));
	}
	
	unsigned int timer::days(const unsigned int total_secs)
	{
		return(total_secs / timer::SECS_PER_DAY);
	}
	
	unsigned int timer::hours(void) const
	{
		return(this->hours(this->total_secs()));
	}
	
	unsigned int timer::hours(const unsigned int total_secs)
	{
		unsigned int left = timer::after_days(total_secs);
	
		return(left / timer::SECS_PER_HOUR);
	}
	
	unsigned int timer::mins(void) const
	{
		return(timer::mins(this->total_secs()));
	}
	
	unsigned int timer::mins(const unsigned int total_secs)
	{
		unsigned int left = timer::after_hours(total_secs);
	
		return(left / timer::SECS_PER_MIN);
	}

	void timer::reset(void)
	{
		this->ticks = 0;
	}

	unsigned int timer::secs(void) const
	{
		return(this->after_mins(this->total_secs()));
	}

	bool timer::start(void)
	{
		if(!this->running)
			return(this->running = (install_param_int_ex(timer::tick, this, BPS_TO_TIMER(1)) == 0));
		return(true);
	}

	void timer::stop(void)
	{
		remove_param_int(timer::tick, this);
		this->running = false;
	}

/*	boost::shared_ptr<char> timer::to_str(int &size) const
	{
		const char *fmt = "%03d:%02d:%02d:%02d";
		const int minsize = 12 + 1;
		int days = this->days();
		boost::shared_ptr<char> str;

		if((size = snprintf(NULL, 0, fmt, days, this->hours(), this->mins(),
				this->secs()) + 1) < minsize)
		{
			size = minsize;
		}

		str.reset(new char[size]);

		snprintf(str.get(), size, fmt, days, this->hours(), this->mins(),
				this->secs());

		str.get()[size] = 0;

		return(str);
	}*/

	std::string timer::to_str(void) const
	{
		unsigned int val[] = {this->days(), this->hours(), this->mins(), this->secs()};
		const char sep = ':';
		const std::streamsize paddedsize = 2;
		std::streamsize strsize;
		std::stringstream ss;

		ss.fill('0');
		strsize = ss.width(3);
		ss << val[0];

		for(int i=1, len=sizeof(val)/sizeof(unsigned int); i<len; i++)
		{
			ss << sep;

			ss.width(paddedsize);
			ss << val[i];

			ss.width(strsize);
		}

		return(ss.str());
	}

	float timer::total_days(void) const
	{
		return((float)this->total_secs() / (float)this->SECS_PER_DAY);
	}
	
	float timer::total_hours(void) const
	{
		return((float)this->total_secs() / (float)this->SECS_PER_HOUR);
	}
	
	float timer::total_mins(void) const
	{
		return((float)this->total_secs() / (float)this->SECS_PER_MIN);
	}
	
	unsigned int timer::total_secs(void) const
	{
		return(this->ticks);
	}
	
	void timer::tick(void *self)
	{
		((timer *)self)->ticks++;
	}
	END_OF_FUNCTION(timer::tick)
}

