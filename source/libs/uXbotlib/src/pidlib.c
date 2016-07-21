/*
 * 	\file pidlib.c
 *
 *  \date 	01/07/2010
 *  \author uXbot
 */
#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif

#include "motorlib.h"

/** Internal variables */
static float 		m_Kp, m_Kd, m_Ki;
static int32_t 		m_max_speed, m_min_speed, m_base_speed;
static int32_t		last_error;
static int32_t		integral_error;





/** PID controller initialization 
	@param Kp: Proportional constant
	@param Kd: Derivative constant
	@param Ki: Integral constant
	@param base_speed		-	uXbot base speed
	@param max_speed		-	Max. speed of the motors (0 to 100)
	@param min_speed		-	Min. speed of the motors (0 to 100) (The lowest value for the motors will be -min_speed)
	*/
void initialize_PID(float Kp, float Kd, float Ki, int8_t base_speed, int8_t max_speed, int8_t min_speed)
{
	m_Kp	=	Kp;
	m_Kd	=	Kd;
	m_Ki	=	Ki;
	m_max_speed 		=	max_speed;
	m_min_speed			=	min_speed;
	m_base_speed		=	base_speed;
	last_error			=	0;
	integral_error		=	0;
}

	
/** Execute the PID controller and update motor speeds
	It's crucial that this function is called at a constant frequency
	@param	error -	Estimated error
	*/
void execute_PID(int error)
{
	float		PID;
	int32_t 	derivative_term;
	int32_t		m_right_motor, m_left_motor;
	
	derivative_term = error - last_error;			///< Compute derivative term
	integral_error += error;						///< Compute integral term
	
	/// Integral term anti wind-up 
	if( (error==0) || (error > 0 && last_error < 0) || (error < 0 && last_error > 0) )
		integral_error = 0;
		
	PID = m_Kp*error + m_Kd*derivative_term + m_Ki*integral_error;		///< Compute PID equation
	m_right_motor 	= m_base_speed + PID;
	m_left_motor	= m_base_speed - PID;
	
	last_error=error;
	/// Comprobar que no excedemos las velocidades máximas/mínima
	if		(m_right_motor > m_max_speed)			m_right_motor = m_max_speed;
	else if (m_right_motor < m_min_speed)			m_right_motor = m_min_speed;
	
	if		(m_left_motor > m_max_speed)			m_left_motor = m_max_speed;
	else if (m_left_motor < m_min_speed)			m_left_motor = m_min_speed;
	
	uXbot_move(m_left_motor, m_right_motor);	///< Update speeds
	
}