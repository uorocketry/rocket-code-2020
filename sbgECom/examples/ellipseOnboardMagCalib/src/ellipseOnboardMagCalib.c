/*!
 *	\file		ellipseOnboardMagCalib.c
 *  \author		SBG Systems (Alexis GUINAMARD)
 *	\date		30/06/2014
 *
 *	\brief		C example that demonstrates the onboard magnetic calibration procedure.
 *
 *	The onboard magnetic calibration is done with the three following steps:
 *		- Acquire some magnetic field data
 *		- Compute a magnetic calibration
 *		- Apply the newly computed magnetic calibration
 *
 *	\section CodeCopyright Copyright Notice 
 *	Copyright (C) 2007-2014, SBG Systems SAS. All rights reserved.
 *	
 *	This source code is intended for use only by SBG Systems SAS and
 *	those that have explicit written permission to use it from
 *	SBG Systems SAS.
 *	
 *	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 *	KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *	IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 *	PARTICULAR PURPOSE.
 */
#include <sbgEComLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------//
//  Private methods                                                    //
//----------------------------------------------------------------------//

/*!
 *	Display magnetic calibration results on the console.
 *	\param[in]	mode							Define which magnetic calibration type has been performed. It could be 3D or 2D
 *	\param[in]	pMagCalibResults				Pointer on a read only magnetic calibration results structure.
 */
void displayMagCalibResults(SbgEComMagCalibMode mode, const SbgEComMagCalibResults *pMagCalibResults)
{
	//
	// Display the magnetic calibration results
	//
	printf("\n\n======== Magnetic calibration report ========\n");
	
	//
	// Convert the quality indicator to human readable output
	//
	switch (pMagCalibResults->quality)
	{
	case SBG_ECOM_MAG_CALIB_QUAL_OPTIMAL:
		printf("Quality:\t\toptimal\n");
		break;
	case SBG_ECOM_MAG_CALIB_QUAL_GOOD:
		printf("Quality:\t\tgood\n");
		break;
	case SBG_ECOM_MAG_CALIB_QUAL_POOR:
		printf("Quality:\t\tpoor\n");
		break;
	default:
		printf("Quality:\t\tundefined\n");
	}

	//
	// Convert the confidence indicator to human readable output
	//
	switch (pMagCalibResults->confidence)
	{
	case SBG_ECOM_MAG_CALIB_TRUST_HIGH:
		printf("Confidence:\t\thigh\n");
		break;
	case SBG_ECOM_MAG_CALIB_TRUST_MEDIUM:
		printf("Confidence:\t\tmedium\n");
		break;
	case SBG_ECOM_MAG_CALIB_TRUST_LOW:
		printf("Confidence:\t\tlow\n");
		break;
	default:
		printf("Confidence:\t\tundefined\n");
	}

	//
	// Print advanced status
	//
	printf("Advanced Status:\n");
	if (pMagCalibResults->advancedStatus & SBG_ECOM_MAG_CALIB_NOT_ENOUGH_POINTS)
	{
		printf("\t- Not enough valid points. Maybe you are moving too fast.\n");
	}
	if (pMagCalibResults->advancedStatus & SBG_ECOM_MAG_CALIB_TOO_MUCH_DISTORTIONS)
	{
		printf("\t- Unable to find a calibration solution. Maybe there are too much non static distortions.\n");
	}
	if (pMagCalibResults->advancedStatus & SBG_ECOM_MAG_CALIB_ALIGNMENT_ISSUE)
	{
		printf("\t- The magnetic calibration has troubles to correct the magnetometers and inertial frame alignment.\n");
	}

	//
	// Test if we have a 2D or 3D calibration mode
	//
	if (mode == SBG_ECOM_MAG_CALIB_MODE_2D)
	{
		//
		// In 2D mode, a X or Y motion issue means we have too much motion
		//
		if (pMagCalibResults->advancedStatus & SBG_ECOM_MAG_CALIB_X_MOTION_ISSUE)
		{
			printf("\t- Too much roll motion for a 2D magnetic calibration.\n");
		}
		if (pMagCalibResults->advancedStatus & SBG_ECOM_MAG_CALIB_Y_MOTION_ISSUE)
		{
			printf("\t- Too much pitch motion for a 2D magnetic calibration.\n");
		}
	}
	else
	{
		//
		// In 3D mode, a X or Y motion issue means we have not enough motion
		//
		if (pMagCalibResults->advancedStatus & SBG_ECOM_MAG_CALIB_X_MOTION_ISSUE)
		{
			printf("\t- Not enough roll motion for a 3D magnetic calibration.\n");
		}
		if (pMagCalibResults->advancedStatus & SBG_ECOM_MAG_CALIB_Y_MOTION_ISSUE)
		{
			printf("\t- Not enough pitch motion for a 3D magnetic calibration.\n");
		}
	}

	//
	// Test if we had enough yaw motion to compute a calibration
	//
	if (pMagCalibResults->advancedStatus & SBG_ECOM_MAG_CALIB_Z_MOTION_ISSUE)
	{
		//
		// Test if we are in
		printf("\t- Not enough yaw motion to compute a valid magnetic calibration.\n");
	}
	
	//
	// Display the number of points used to compute the magnetic calibration
	//
	printf("\n\n");
	printf("Used Points:\t%u\n", pMagCalibResults->numPoints);
	printf("Max Points:\t%u\n", pMagCalibResults->maxNumPoints);

	//
	// Display magnetic field deviation errors
	//
	printf("\n\n-------------------------------------\n");
	printf("Magnetic field deviation report\n");
	printf("-------------------------------------\n");
	printf("\t\tMean\tStd\tMax\n");
	printf("Before\t\t%0.2f\t%0.2f\t%0.2f\n", pMagCalibResults->beforeMeanError, pMagCalibResults->beforeStdError, pMagCalibResults->beforeMaxError);
	printf("After\t\t%0.2f\t%0.2f\t%0.2f\n", pMagCalibResults->afterMeanError, pMagCalibResults->afterStdError, pMagCalibResults->afterMaxError);
	printf("Accuracy (deg)\t%0.2f\t%0.2f\t%0.2f\n", sbgRadToDegF(pMagCalibResults->meanAccuracy), sbgRadToDegF(pMagCalibResults->stdAccuracy), sbgRadToDegF(pMagCalibResults->maxAccuracy));
	printf("\n\n\n");
}

//----------------------------------------------------------------------//
//  Main program                                                        //
//----------------------------------------------------------------------//

/*!
 *	Main entry point.
 *	\param[in]	argc		Number of input arguments.
 *	\param[in]	argv		Input arguments as an array of strings.
 *	\return					0 if no error and -1 in case of error.
 */
int main(int argc, char** argv)
{
	SbgEComHandle			comHandle;
	SbgErrorCode			errorCode;
	SbgInterface			sbgInterface;
	int32					retValue = 0;
	SbgEComDeviceInfo		deviceInfo;
	SbgEComMagCalibResults	magCalibResults;
	SbgEComMagCalibMode		mode;

	//
	// Create an interface: 
	// We can choose either a serial for real time operation, or file for previously logged data parsing
	// Note interface closing is also differentiated !
	//
	errorCode = sbgInterfaceSerialCreate(&sbgInterface, "/dev/cu.usbserial-FTX2GE57", 921600);		// Example for Unix using a FTDI Usb2Uart converter
	//errorCode = sbgInterfaceSerialCreate(&sbgInterface, "COM23", 115200);								// Example for Windows serial communication

	//
	// Test that the interface has been created
	//
	if (errorCode == SBG_NO_ERROR)
	{
		//
		// Create the sbgECom library and associate it with the created interfaces
		//
		errorCode = sbgEComInit(&comHandle, &sbgInterface);

		//
		// Test that the sbgECom has been initialized
		//
		if (errorCode == SBG_NO_ERROR)
		{
			printf("sbgECom properly Initialized.\n");
			printf("sbgECom version %s\n\n", SBG_E_COM_VERSION_STR);

			//
			// Get device information
			//
			errorCode = sbgEComCmdGetInfo(&comHandle, &deviceInfo);

			//
			// Display device information if no error
			//
			if (errorCode == SBG_NO_ERROR)
			{
				printf("Device : %0.9u found\n", deviceInfo.serialNumber);
			}
			else
			{
				fprintf(stderr, "ellipseOnboardMagCalib: Unable to get device information.\n");
			}

			//
			// Define the calibration mode to perform
			//
			mode = SBG_ECOM_MAG_CALIB_MODE_3D;

			//
			// Start / reset the acquisition of magnetic field data
			// Each time this command is called, the device is prepared to acquire a new set of magnetic field data
			// You have to specify here if the magnetic field data acquisition will be used to compute a 2D or 3D calibration
			//
			errorCode = sbgEComCmdMagStartCalib(&comHandle, mode, SBG_ECOM_MAG_CALIB_HIGH_BW);

			//
			// Make sure that the magnetic calibration has started
			//
			if (errorCode == SBG_NO_ERROR)
			{
				//
				// The device is now acquiring some magnetic field data.
				// Wait for a user input before computing the magnetic calibration
				//
				printf("The device is acquiring magnetic field data.\n\nPress enter to stop the magnetic field acquisition.\n");
				fgetc(stdin);

				//
				// Try to compute a magnetic calibration and get the results
				//
				errorCode = sbgEComCmdMagComputeCalib(&comHandle, &magCalibResults);

				//
				// Make sure that we were able to get magnetic calibration results
				//
				if (errorCode == SBG_NO_ERROR)
				{
					//
					// Test if the device has computed a valid magnetic calibration
					//
					if (magCalibResults.quality != SBG_ECOM_MAG_CALIB_QUAL_INVALID)
					{
						//
						// Send the new magnetic calibration data
						//
						errorCode = sbgEComCmdMagSetCalibData(&comHandle, magCalibResults.offset, magCalibResults.matrix);

						//
						// Make sure that the new magnetic calibration data has been updated
						//
						if (errorCode == SBG_NO_ERROR)
						{
							printf("The new magnetic calibration has been applied.\n");

							//
							// Display the magnetic calibration status
							//
							displayMagCalibResults(mode, &magCalibResults);
						}
						else
						{
							fprintf(stderr, "ellipseOnboardMagCalib: Unable to upload new magnetic calibration data.\n");
						}
					}
					else
					{
						//
						// Unable to compute a valid magnetic calibration
						//
						fprintf(stderr, "ellipseOnboardMagCalib: Unable to compute a valid magnetic calibration.\n");
					}
				}
				else
				{
					fprintf(stderr, "ellipseOnboardMagCalib: Unable to get onboard magnetic calibration results.\n");
				}
			}
			else
			{
				fprintf(stderr, "ellipseOnboardMagCalib: Unable to start the onboard magnetic calibration.\n");
			}

			//
			// Close the sbgEcom library
			//
			sbgEComClose(&comHandle);
		}
		else
		{
			//
			// Unable to initialize the sbgECom
			//
			fprintf(stderr, "ellipseOnboardMagCalib: Unable to initialize the sbgECom library.\n");
			retValue = -1;
		}
		
		//
		// Close the interface
		//
		sbgInterfaceSerialDestroy(&sbgInterface);		
	}
	else
	{
		//
		// Unable to create the interface
		//
		fprintf(stderr, "ellipseOnboardMagCalib: Unable to create the interface.\n");
		retValue = -1;
	}

	//
	// Make a pause before exit
	//
	printf("Press enter to exit the main program\n");
	fgetc(stdin);

	//
	// Returns -1 if we have an error
	//
	return retValue;
}
