#pragma once

class CCar
{
public:
	CCar();
	
	enum direction
	{
		BACKWARD,
		STAY,
		FORWARD
	};

	bool IsEngineTurnedOn() const;
	direction GetDirection() const;
	size_t GetSpeed() const;
	int GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetSpeed(int speed);
	bool SetGear(int gear);

private:
	struct range
	{
		size_t from, to;
	};
	static range m_gearSpeeds[];

	bool m_isEngineTurnedOn;
	bool m_needStop;
	direction m_direction;
	size_t m_speed;
	int m_gear;

};

