#include "stdafx.h"
#include "Car.h"

CCar::range CCar::m_gearSpeeds[] = { { 0, 20 }, { 0, 150 }, {0, 30}, { 20, 50 }, { 30, 60 }, { 40, 90 }, { 50, 150 } };

CCar::CCar():
	m_isEngineTurnedOn(false),
	m_needStop(false),
	m_direction(direction::STAY),
	m_speed(0),
	m_gear(0)
{
}

bool CCar::IsEngineTurnedOn() const
{
	return m_isEngineTurnedOn;
}

CCar::direction CCar::GetDirection() const
{
	return m_direction;
}

size_t CCar::GetSpeed() const
{
	return m_speed;
}

int CCar::GetGear() const
{
	return m_gear;
}

bool CCar::TurnOnEngine()
{
	if (!m_isEngineTurnedOn)
	{
		m_isEngineTurnedOn = true;
		m_gear = 0;
		m_speed = 0;
		m_direction = direction::STAY;
		return true;
	}
	return false;
}

bool CCar::TurnOffEngine()
{
	if (m_isEngineTurnedOn)
	{
		if (m_gear == 0 && m_speed == 0 && m_direction == direction::STAY)
		{
			m_isEngineTurnedOn = false;
			return true;
		}
	}

	return false;
}

bool CCar::SetSpeed(unsigned speed)
{
	if (!m_isEngineTurnedOn)
	{
		return false;
	}

	if (m_gear == 0)
	{
		if (speed < m_speed)
		{
			if (speed == 0)
			{
				m_needStop = false;
				m_direction = direction::STAY;
			}
			m_speed = speed;
			return true;
		}
		return false;
	}

	if (speed >= m_gearSpeeds[m_gear + 1].from && speed <= m_gearSpeeds[m_gear + 1].to)
	{
		if (speed == 0)
		{
			m_needStop = false;
			m_direction = direction::STAY;
		}
		if (m_speed == 0 && speed > 0)
		{
			if (m_gear > -1)
			{
				m_direction = direction::FORWARD;
			}
			else
			{
				m_direction = direction::BACKWARD;
			}
		}
		m_speed = speed;
		return true;
	}

	return false;
}

bool CCar::SetGear(int gear)
{
	if (gear < -1 || gear > 5)
	{
		return false;
	}

	if (gear == m_gear)
	{
		return true;
	}

	if (!m_isEngineTurnedOn)
	{
		if (gear == 0)
		{
			m_gear = 0;
			return true;
		}
		return false;
	}

	if (m_speed >= m_gearSpeeds[gear + 1].from && m_speed <= m_gearSpeeds[gear + 1].to)
	{
		if (gear == -1)
		{
			if (m_speed == 0)
			{
				m_gear = -1;
				return true;
			}
			return false;
		}

		if (gear == 1 && m_gear == -1)
		{
			if (m_speed == 0)
			{
				m_gear = 1;
				return true;
			}
			return false;
		}

		if (m_gear == 0 && gear == 1 && m_needStop)
		{
			return false;
		}
		m_needStop = false;
		if (m_gear == -1 && gear == 0 && m_speed != 0)
		{
			m_needStop = true;
		}

		m_gear = gear;

		return true;
	}

	return false;
}
