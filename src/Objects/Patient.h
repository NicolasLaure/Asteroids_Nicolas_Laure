#pragma once

namespace asteroids
{
	struct Patient
	{
		int patientHealth;
	};

	void PatientTakeDamage(Patient& patient, bool& isGameOver);
}