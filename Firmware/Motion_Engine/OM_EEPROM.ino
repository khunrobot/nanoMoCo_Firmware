/*


Motion Engine

See dynamicperception.com for more information


(c) 2008-2012 C.A. Church / Dynamic Perception LLC

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


*/



/*

  ========================================
  EEPROM write/read functions
  ========================================
  
*/




// EEPROM Memory Layout Version, change this any time you modify what is stored
const unsigned int MEMORY_VERSION = 5;




/** Check EEPROM Status

 If EEPROM hasn't been stored, or EEPROM version does not
 match our version, it saves our variables to eeprom memory.
 
 Otherwise, it reads stored variables from EEPROM memory
 
 @author C. A. Church
 */
 
void eepromCheck() {
  
  using namespace OMEEPROM;
    
  if( saved() ) {
      if( version() != MEMORY_VERSION )
        eepromWrite();
      else
        eepromRestore();
  }
  else {
    eepromWrite();
  }
    
}

 /** Write All Variables to EEPROM */
 
void eepromWrite() {
  using namespace OMEEPROM;
 
  version(MEMORY_VERSION);
  
  write(EE_ADDR, device_address);
  write(EE_NAME, *device_name, 10);
  
	long tempPos = 0;
	long tempEnd = 0;
	long tempStart = 0;
	long tempStop = 0;
	byte tempMS = 0;
	bool tempSleep = false;
	
	for (int i = 0; i < MOTOR_COUNT; i++){
		
		tempPos   = motor[i].currentPos();
		tempEnd   = motor[i].endPos();
		tempStart = motor[i].startPos();
		tempStop  = motor[i].stopPos();
		tempMS    = motor[i].ms();
		tempSleep = motor[i].sleep();

		write(EE_POS_0   + EE_MOTOR_MEMORY_SPACE * i, tempPos);
		write(EE_END_0   + EE_MOTOR_MEMORY_SPACE * i, tempEnd);
		write(EE_START_0 + EE_MOTOR_MEMORY_SPACE * i, tempStart);
		write(EE_STOP_0  + EE_MOTOR_MEMORY_SPACE * i, tempStop);
		write(EE_MS_0    + EE_MOTOR_MEMORY_SPACE * i, tempMS);
		write(EE_SLEEP_0 + EE_MOTOR_MEMORY_SPACE * i, tempSleep);
		
	}
 
}


 /** Read all variables from EEPROM */
 
void eepromRestore() {
  using namespace OMEEPROM;
  
	read(EE_ADDR, device_address);
	read(EE_NAME, *device_name, 10);
	
	// There had been problems with reading the EEPROM values inside the motor setting functions,
	// so as a work around, they are saved into these temporary variables which are then used to load
	// the proper motor settings.
	long tempPos = 0;
	long tempEnd = 0;
	long tempStart = 0;
	long tempStop = 0;
	byte tempMS = 0;
	bool tempSleep = false;
	
	
	for (int i = 0; i < MOTOR_COUNT; i++){

		read(EE_POS_0   + EE_MOTOR_MEMORY_SPACE * i, tempPos);
		read(EE_END_0   + EE_MOTOR_MEMORY_SPACE * i, tempEnd);
		read(EE_START_0 + EE_MOTOR_MEMORY_SPACE * i, tempStart);
		read(EE_STOP_0  + EE_MOTOR_MEMORY_SPACE * i, tempStop);
		read(EE_MS_0    + EE_MOTOR_MEMORY_SPACE * i, tempMS);
		read(EE_SLEEP_0 + EE_MOTOR_MEMORY_SPACE * i, tempSleep);
		
		motor[i].ms(tempMS);
		motor[i].currentPos(tempPos);
		motor[i].endPos(tempEnd);
		motor[i].startPos(tempStart);
		motor[i].stopPos(tempStop);
		motor[i].sleep(tempSleep);
		
			
	}

}


