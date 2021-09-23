#include "config/config.h"

#if USE_SBG == 1

#include "SBGSensor.h"

#include "iostream"

//----------------------------------------------------------------------//
//  Call backs                                                          //
//----------------------------------------------------------------------//

/*!
 *	Callback definition called each time a new log is received.
 *	\param[in]	pHandle
 *Valid handle on the sbgECom instance that has called this callback. \param[in]
 *msgClass								Class of the
 *message we have received \param[in]	msg Message ID of the log received.
 *\param[in]
 *pLogData								Contains the
 *received log data as an union. \param[in]	pUserArg Optional user supplied
 *argument. \return SBG_NO_ERROR if the received log has been used successfully.
 */
SbgErrorCode onLogReceived(SbgEComHandle *pHandle, SbgEComClass msgClass, SbgEComMsgId msg,
                           const SbgBinaryLogData *pLogData, void *pUserArg)
{
    //
    // Handle separately each received data according to the log ID
    //
    // std::cout << pUserArg;
    auto *sens = (SBGSensor *)pUserArg;
    std::lock_guard<std::mutex> lockGuard(sens->mutex);

    switch (msg)
    {
    case SBG_ECOM_LOG_GPS1_POS:
        //
        // Simply display GPS Position in real time
        // latitude longitude altitude
        sens->data.gpsLatitude = pLogData->gpsPosData.latitude;
        sens->data.gpsLongitude = pLogData->gpsPosData.longitude;
        sens->data.gpsAltitude = pLogData->gpsPosData.altitude;
        sens->data.gpsPosStatus = pLogData->gpsPosData.status;
        sens->data.gpsPosAccuracyLatitude = pLogData->gpsPosData.latitudeAccuracy;
        sens->data.gpsPosAccuracyLongitude = pLogData->gpsPosData.longitudeAccuracy;
        sens->data.gpsPosAccuracyAltitude = pLogData->gpsPosData.altitudeAccuracy;
        sens->data.NumSvUsed = pLogData->gpsPosData.numSvUsed;

        break;

    case SBG_ECOM_LOG_EKF_EULER:
        //
        // Simply display euler angles in real time
        //
        // printf("euler Angles: %3.1f\t%3.1f\t%3.1f\tStd Dev:%3.1f\t%3.1f\t%3.1f
        // \r\n", 		sbgRadToDegF(pLogData->ekfEulerData.euler[0]),
        // sbgRadToDegF(pLogData->ekfEulerData.euler[1]),
        // sbgRadToDegF(pLogData->ekfEulerData.euler[2]),
        // sbgRadToDegF(pLogData->ekfEulerData.eulerStdDev[0]),
        // sbgRadToDegF(pLogData->ekfEulerData.eulerStdDev[1]),
        // sbgRadToDegF(pLogData->ekfEulerData.eulerStdDev[2]));

        sens->data.roll = sbgRadToDegF(pLogData->ekfEulerData.euler[0]);
        sens->data.pitch = sbgRadToDegF(pLogData->ekfEulerData.euler[1]);
        sens->data.yaw = sbgRadToDegF(pLogData->ekfEulerData.euler[2]);
        sens->data.rollAccuracy = sbgRadToDegF(pLogData->ekfEulerData.eulerStdDev[0]);
        sens->data.pitchAccuracy = sbgRadToDegF(pLogData->ekfEulerData.eulerStdDev[1]);
        sens->data.yawAccuracy = sbgRadToDegF(pLogData->ekfEulerData.eulerStdDev[2]);
        break;

    case SBG_ECOM_LOG_EKF_NAV:
        // 	//
        // 	// Speed
        // 	//
        sens->data.velocityN = pLogData->ekfNavData.velocity[0];
        sens->data.velocityE = pLogData->ekfNavData.velocity[1];
        sens->data.velocityD = pLogData->ekfNavData.velocity[2];

        sens->data.solutionStatus = pLogData->ekfNavData.status;

        sens->data.velocityNAccuracy = pLogData->ekfNavData.velocityStdDev[0];
        sens->data.velocityEAccuracy = pLogData->ekfNavData.velocityStdDev[1];
        sens->data.velocityDAccuracy = pLogData->ekfNavData.velocityStdDev[2];

        sens->data.latitudeAccuracy = pLogData->ekfNavData.positionStdDev[0];
        sens->data.longitudeAccuracy = pLogData->ekfNavData.positionStdDev[1];
        sens->data.altitudeAccuracy = pLogData->ekfNavData.positionStdDev[2];

        // 	// printf("Vel x Vel Y Vel Z: %3.6f\t%3.6f\t%3.6f\t   \r\n",
        // 			// pLogData->ekfNavData.velocity[0],
        // pLogData->ekfNavData.velocity[1], pLogData->ekfNavData.velocity[2]);

        break;
    case SBG_ECOM_LOG_PRESSURE:
        sens->data.barometricAltitude = pLogData->pressureData.height;
        sens->data.relativeBarometricAltitude = pLogData->pressureData.height - sens->barometricAltitudeOffset;

        sens->data.pressureStatus = pLogData->pressureData.status;
        sens->data.barometricPressure = pLogData->pressureData.pressure;

        break;

    case SBG_ECOM_LOG_IMU_DATA:
        // sens->data.filteredroll =
        // sbgRadToDegF(pLogData->imuData.gyroscopes[0]); sens->data.filteredpitch
        // = sbgRadToDegF(pLogData->imuData.gyroscopes[1]); sens->data.filteredyaw
        // = sbgRadToDegF(pLogData->imuData.gyroscopes[2]);
        sens->data.filteredXaccelerometer = pLogData->imuData.accelerometers[0];
        sens->data.filteredYaccelerometer = pLogData->imuData.accelerometers[1];
        sens->data.filteredZaccelerometer = pLogData->imuData.accelerometers[2];

        sens->data.imuStatus = pLogData->imuData.status;

        sens->data.gyroX = pLogData->imuData.gyroscopes[0];
        sens->data.gyroY = pLogData->imuData.gyroscopes[1];
        sens->data.gyroZ = pLogData->imuData.gyroscopes[2];

        sens->data.temp = pLogData->imuData.temperature;

        sens->data.deltaVelX = pLogData->imuData.deltaVelocity[0];
        sens->data.deltaVelY = pLogData->imuData.deltaVelocity[1];
        sens->data.deltaVelZ = pLogData->imuData.deltaVelocity[2];

        sens->data.deltaAngleX = pLogData->imuData.deltaAngle[0];
        sens->data.deltaAngleY = pLogData->imuData.deltaAngle[1];
        sens->data.deltaAngleZ = pLogData->imuData.deltaAngle[2];

        break;
    default:
        break;
    }

    return SBG_NO_ERROR;
}

//----------------------------------------------------------------------//
//  Main program                                                        //
//----------------------------------------------------------------------//

/*!
 *	Main entry point.
 *	\param[in]	argc		Number of input arguments.
 *	\param[in]	argv		Input arguments as an array of strings.
 *	\return					0 if no error and -1 in case of
 *error.
 */

void SBGSensor::run()
{
    SbgEComHandle comHandle;
    SbgErrorCode errorCode;
    SbgInterface sbgInterface;
    int32 retValue = 0;
    SbgEComDeviceInfo deviceInfo;

    //
    // Create an interface:
    // We can choose either a serial for real time operation, or file for
    // previously logged data parsing Note interface closing is also
    // differentiated !
    //
    errorCode = sbgInterfaceSerialCreate(&sbgInterface, "/dev/ttyUSB0",
                                         115200); // Example for Unix using a FTDI Usb2Uart converter
    // errorCode = sbgInterfaceSerialCreate(&sbgInterface, "COM3", 115200);
    // // Example for Windows serial communication

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
            //
            // Get device inforamtions
            //
            errorCode = sbgEComCmdGetInfo(&comHandle, &deviceInfo);

            //
            // Display device information if no error
            //
            if (errorCode == SBG_NO_ERROR)
            {
                // printf("Device : %0.9u found\n", deviceInfo.serialNumber);
                printf("Device found\n");
            }
            else
            {
                fprintf(stderr, "ellipseMinimal: Unable to get device information.\n");
            }

            // std::cout <<
            // sbgEComLogEkfBuildSolutionStatus(SBG_ECOM_SOL_MODE_UNINITIALIZED,
            // 0b0000) << "\n";

            //
            // Configure some output logs to 25 Hz
            //
            // if (sbgEComCmdOutputSetConf(&comHandle, SBG_ECOM_OUTPUT_PORT_A,
            // SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_EKF_NAV,
            // SBG_ECOM_OUTPUT_MODE_MAIN_LOOP) != SBG_NO_ERROR)
            // {
            // 	fprintf(stderr, "ellipseMinimal: Unable to configure output log
            // SBG_ECOM_LOG_EKF_NAV.\n");
            // }
            // if (sbgEComCmdOutputSetConf(&comHandle, SBG_ECOM_OUTPUT_PORT_A,
            // SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_IMU_DATA,
            // SBG_ECOM_OUTPUT_MODE_MAIN_LOOP) != SBG_NO_ERROR)
            // {
            // 	fprintf(stderr, "ellipseMinimal: Unable to configure output log
            // SBG_ECOM_LOG_IMU_DATA.\n");
            // }
            // if (sbgEComCmdOutputSetConf(&comHandle, SBG_ECOM_OUTPUT_PORT_A,
            // SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_EKF_EULER,
            // SBG_ECOM_OUTPUT_MODE_MAIN_LOOP) != SBG_NO_ERROR)
            // {
            // 	fprintf(stderr, "ellipseMinimal: Unable to configure output log
            // SBG_ECOM_LOG_EKF_EULER.\n");
            // }
            // if (sbgEComCmdOutputSetConf(&comHandle, SBG_ECOM_OUTPUT_PORT_A,
            // SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_GPS1_POS,
            // SBG_ECOM_OUTPUT_MODE_DIV_8) != SBG_NO_ERROR)
            // {
            // 	fprintf(stderr, "ellipseMinimal: Unable to configure output log
            // SBG_ECOM_LOG_GPS1_POS.\n");
            // }
            // if (sbgEComCmdOutputSetConf(&comHandle, SBG_ECOM_OUTPUT_PORT_A,
            // SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_PRESSURE,
            // SBG_ECOM_OUTPUT_MODE_DIV_8) != SBG_NO_ERROR)
            // {
            // 	fprintf(stderr, "ellipseMinimal: Unable to configure output log
            // SBG_ECOM_LOG_PRESSURE.\n");
            // }

            //
            // Display a message for real time data display
            //
            printf("sbgECom properly Initialized.\n");
            printf("sbgECom version %s\n\n", SBG_E_COM_VERSION_STR);
            printf("Euler Angles display with estimated standard deviation.\n");

            //
            // Define callbacks for received data
            //
            sbgEComSetReceiveLogCallback(&comHandle, onLogReceived, this);
            //
            // Loop until the user exist
            //
            while (true)
            {
                //
                // Try to read a frame
                //
                errorCode = sbgEComHandle(&comHandle);

                //
                // Test if we have to release some CPU (no frame received)
                //
                if (errorCode == SBG_NOT_READY)
                {
                    //
                    // Release CPU
                    //
                    sbgSleep(1);
                }
                else
                {
                    fprintf(stderr, "Error\n");
                }
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
            fprintf(stderr, "ellipseMinimal: Unable to initialize the sbgECom library.\n");
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
        fprintf(stderr, "ellipseMinimal: Unable to create the interface.\n");
        retValue = -1;
    }

    // Returns -1 if we have an error
    // return retValue;
}

void SBGSensor::initialize()
{
    IO::initialize();
}

bool SBGSensor::isInitialized()
{
    return ((data.solutionStatus & 0b1111) == 4);
}

void SBGSensor::setZeroBarometricAltitude()
{
    barometricAltitudeOffset = data.barometricAltitude;
}

sbgData SBGSensor::getData()
{
    std::lock_guard<std::mutex> lockGuard(mutex);
    return data;
}

#endif