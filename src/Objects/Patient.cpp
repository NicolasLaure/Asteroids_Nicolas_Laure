#include "Objects/Patient.h"

void PatientTakeDamage(Patient& patient, bool& isGameOver)
{
	patient.patientHealth--;
	if (patient.patientHealth <= 0)
		isGameOver = true;
}