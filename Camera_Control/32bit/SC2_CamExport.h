//-----------------------------------------------------------------//
// Name        | SC2_CamExport.h             | Type: ( ) source    //
//-------------------------------------------|       (*) header    //
// Project     | PCO                         |       ( ) others    //
//-----------------------------------------------------------------//
// Platform    | PC                                                //
//-----------------------------------------------------------------//
// Environment | Visual 'C++'                                      //
//-----------------------------------------------------------------//
// Purpose     | PCO - SC2 Camera DLL Functions                    //
//-----------------------------------------------------------------//
// Author      | FRE, PCO AG                                       //
//-----------------------------------------------------------------//
// Revision    |  rev. 1.10 rel. 1.10                              //
//-----------------------------------------------------------------//
// Notes       | Some functions are illustrated with an example    //
//             | source code. If the function you need doesn't     //
//             | have some source code sample, please take a look  //
//             | on other functions supplied with source code. You //
//             | will find some usefull code there and you will be //
//             | able to adapt the code to the function you need.  //
//             |                                                   //
//             | To get informations about the ranges of the       //
//             | data values please take a look at the SDK docu.   //
//-----------------------------------------------------------------//
// (c) 2002 PCO AG * Donaupark 11 *                                //
// D-93309      Kelheim / Germany * Phone: +49 (0)9441 / 2005-0 *  //
// Fax: +49 (0)9441 / 2005-20 * Email: info@pco.de                 //
//-----------------------------------------------------------------//


//-----------------------------------------------------------------//
// Revision History:                                               //
//-----------------------------------------------------------------//
// Rev.:     | Date:      | Changed:                               //
// --------- | ---------- | ---------------------------------------//
//  0.10     | 03.07.2003 |  new file, FRE                         //
//-----------------------------------------------------------------//
//  0.13     | 08.12.2003 |  Added GetSizes, FRE                   //
//-----------------------------------------------------------------//
//  0.14     | 14.01.2004 |  Added GetCOCRuntime,                  //
//           |            |  Added GetBufferStatus, FRE            //
//-----------------------------------------------------------------//
//  0.15     | 06.02.2004 |  Added SetImagestruct                  //
//           |            |  Added SetStoragestruct                //
//           | 18.02.2004 |  Added Self calibration and correction //
//-----------------------------------------------------------------//
//  0.16     | 23.03.2004 |  Removed single entries for dwDelay    //
//           |            |  and dwExposure, now they are part of  //
//           |            |  the delay/exposure table, FRE         //
//-----------------------------------------------------------------//
//  1.0      | 04.05.2004 |  Released to market                    //
//           |            |                                        //
//-----------------------------------------------------------------//
//  1.01     | 04.05.2004 |  Added FPSExposureMode, FRE            //
//           |            |  Set-Get-1394Transferparameter         //
//-----------------------------------------------------------------//
//  1.02     | 29.07.2004 |  Changed to explicit linking           //
//           |            |  Added CamLink interface capability    //
//           | 23.07.2004 |  Added OpenCameraEx                    //
//           | 06.10.2004 |  Added SetTimeouts                     //
//           | 10.11.2004 |  Added GetBuffer                       //
//-----------------------------------------------------------------//
//  1.03     | 22.02.2005 |  Added AddBufferEx and GetImageEx, FRE //
//           |            |  Allocate sizes adapted due to possible//
//           |            |  crash in case of changing the transfer//
//           |            |  parameters.                           //
//-----------------------------------------------------------------//
//  1.04     | 19.04.2005 |  Added PCO_Get(Set)NoiseFilterMode, FRE//
//           |            |  Added try catch blocks where pointer  //
//           |            |  are passed in. Changed the init. where//
//           |            |  an error occured while retrieving data//
//           |            |  Bugfix: GetImage(Ex) is able to trans.//
//           |            |  more than one image, now...           //
//           | 20.07.2005 |  Added record stop event stuff, FRE    //
//-----------------------------------------------------------------//
//  1.05     | 27.02.2006 |  Added PCO_GetCameraName, FRE          //
//           |            |  Added PCO_xxxHotPixelxxx, FRE         //
//-----------------------------------------------------------------//
//  1.06     | 02.06.2006 |  Added PCO_GetCameraDescriptionEx, FRE //
//           |            |  Added PCO_xxxModulationMode, FRE      //
//           |            |  Added PCO_GetInfoString, FRE          //
//-----------------------------------------------------------------//
//  1.08     | 19.09.2007 |  FRE:Added PCO_GetInfoString, FRE      //
//-----------------------------------------------------------------//
//  1.09     | 17.04.2008 |  FRE: Minor corrections, FRE           //
//-----------------------------------------------------------------//
//  1.10     | 05.03.2009 |  FRE: Added Get/SetFrameRate           //
//           |            |  Added HW IO functions and desc.       //
//           |            |  Added PCO_S(G)etInterfaceOutputFormat //
//           | 28.05.2009 |  Added PCO_S(G)etBayerMultiplier,      //
//           |            |  and PCO_GetColorCorrectionMatrix      //
//           | 01.07.2009 |  Added PCO_GetImageTiming              //
//           | 02.07.2009 |  Added PCO_GetFirmWareInfo             //
//-----------------------------------------------------------------//
//  1.11     | 22.10.2009 |  FRE: Added PCO_G(S)etGigEIPAddress    //
//-----------------------------------------------------------------//
//  1.12     | 02.03.2010 |  FRE: Added PCO_G(S)etMetaDataMode     //
//           | 08.03.2010 |  FRE: Added PCO_G(S)etFastTimingMode   //
//-----------------------------------------------------------------//
//  1.13     | 16.11.2010 |  FRE: added                            //
//           |            | PCO_GetCameraSetup, PCO_SetCameraSetup //
//-----------------------------------------------------------------//
//  1.14     | 31.03.2011 |  FRE: added                            //
//           |            | PCO_G(S)etPowerSaveMode                //
//           |            | PCO_GetBatteryStatus                   //
//-----------------------------------------------------------------//

#ifdef SC2_CAM_EXPORTS
#if defined _WIN64
  #define SC2_SDK_FUNC
#else
  #define SC2_SDK_FUNC __declspec(dllexport)
#endif
#else
#define SC2_SDK_FUNC __declspec(dllimport)
#endif

#include "sc2_SDKaddendum.h"
#include "sc2_SDKStructures.h"
#ifdef __cplusplus
extern "C" {            //  Assume C declarations for C++
#endif  //C++

// VERY IMPORTANT INFORMATION:
/*******************************************************************/
/* PLEASE: Do not forget to fill in all wSize Parameters while     */
/* using the structure funtions. Some structures even have embedded*/
/* wSize parameters.                                               */
/*******************************************************************/
/* All indexes, but segment and image parameters are zero based.   */
/* If you access the camera with segment and image parameters the  */
/* base is 1! E.g.
  PCO_Image strImage;
  int err;
  strImage.wSize = sizeof(PCO_Image);
  err = PCO_GetImageStruct(ph, &strImage);

  // Info about segment 1:
  dwValidImageCnt = strImage.strSegment[0].dwValidImageCnt;

  // Info about segment 2:
  dwValidImageCnt = strImage.strSegment[1].dwValidImageCnt;

  // Info about segment 3:
  dwValidImageCnt = strImage.strSegment[2].dwValidImageCnt;

  // Info about segment 4:
  dwValidImageCnt = strImage.strSegment[3].dwValidImageCnt;

but:----Access-To-Segment-1-is----
                                ||
                                \/
  err = PCO_GetSegmentStruct(ph, 1, &strImage.strSegment[0].wSize);

and:
  DWORD dw1stImage = 1; // 1 based !!!!! This accesses the first image.
  DWORD dwLastImage = 2;

again:-Access-To-Segment-1--
                          ||
                          \/
  err = PCO_GetImageEx(ph, 1, dw1stImage, dwLastImage, sBufNr,
                       wXRes, wYRes, wBitPerPixel);
 
/*******************************************************************/

/////////////////////////////////////////////////////////////////////
/////// General commands ////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
SC2_SDK_FUNC int WINAPI PCO_GetGeneral(void* ph, PCO_General *strGeneral);
// Gets all data of the general settings in one structure.
// In: HANDLE ph -> Handle to a previously opened camera.
//     PCO_General *strGeneral -> Pointer to a PCO_General structure.
// Out: int -> Error message.
/* Example:
  HANDLE hCamera;
  ...
  PCO_General strGeneral;
  strGeneral.wSize = sizeof(PCO_General);
  int err = PCO_GetGeneral(hCamera, &strGeneral);
  ...
*/

SC2_SDK_FUNC int WINAPI PCO_GetCameraType(void* ph, PCO_CameraType *strCamType);
// Gets the camera type in one structure.
// In: HANDLE ph -> Handle to a previously opened camera.
//     PCO_CameraType *strCamType -> Pointer to a PCO_CameraType structure.
// Out: int -> Error message.
/* Example:
  HANDLE hCamera;
  ...
  PCO_CameraType strCamType;
  int err = PCO_GetCameraType(hCamera, &strCamType);
  ...
*/

SC2_SDK_FUNC int WINAPI PCO_GetCameraHealthStatus(void* ph, unsigned long* dwWarn, unsigned long* dwErr, unsigned long* dwStatus);
// Gets the last warnings, errors and status of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD *dwWarn -> Pointer to a DWORD variable, to receive the warning value.
//     DWORD *dwErr -> Pointer to a DWORD variable, to receive the error value.
//     DWORD *dwStatus -> Pointer to a DWORD variable, to receive the status value.
// Out: int -> Error message.
/* Example:
  HANDLE hCamera;
  ...
  DWORD dwWarn, DWORD dwErr, DWORD dwStatus
  int err = PCO_GetCameraHealthStatus(hCamera, &dwWarn, &dwErr, &dwStatus);
  ...
*/

SC2_SDK_FUNC int WINAPI PCO_ResetSettingsToDefault(void* ph);
// Resets the camera to a default setting.
// In: HANDLE ph -> Handle to a previously opened camera.
// Out: int -> Error message.
/* Example: see PCO_CloseCamera */

SC2_SDK_FUNC int WINAPI PCO_InitiateSelftestProcedure(void* ph);
// Starts a self test procedure.
// In: HANDLE ph -> Handle to a previously opened camera.
// Out: int -> Error message.
/* Example: see PCO_CloseCamera */

SC2_SDK_FUNC int WINAPI PCO_GetTemperature(void* ph, short* sCCDTemp, short* sCamTemp, short* sPowTemp);
// Gets the actual temperatures of the camera and the power device.
// In: HANDLE ph -> Handle to a previously opened camera.
//     SHORT *sCCDTemp -> Pointer to a SHORT variable, to receive the CCD temp. value.
//     SHORT *sCamTemp -> Pointer to a SHORT variable, to receive the camera temp. value.
//     SHORT *sPowTemp -> Pointer to a SHORT variable, to receive the power device temp. value.
// Out: int -> Error message.
/* Example: see PCO_GetCameraHealthStatus.*/

SC2_SDK_FUNC int WINAPI PCO_GetInfoString(void* ph, unsigned long dwinfotype,
                         char *buf_in, unsigned short size_in);
// Gets the name of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD dwinfotype -> 0: Camera and interface name
//                         1: Camera name only
//                         2: Sensor name
//     char *buf_in -> Pointer to a string, to receive the info string.
//     WORD size_in -> WORD variable which holds the maximum length of the string.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetCameraName(void* ph, char* szCameraName, unsigned short wSZCameraNameLen);
// Gets the name of the camera.
// Not applicable to all cameras.
// In: HANDLE ph -> Handle to a previously opened camera.
//     char *szCameraName -> Pointer to a string, to receive the camera name.
//     WORD wSZCameraNameLen -> WORD variable which holds the maximum length of the string.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetFirmwareInfo(void* ph, unsigned short wDeviceBlock, PCO_FW_Vers* pstrFirmWareVersion);
// Gets the firmware versions of devices in the camera.
// Not applicable to all cameras.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wDeviceBlock -> WORD variable which holds the block to get, e.g. 0->1...10, 1->11...20
//     PCO_FW_Vers* pstrFirmWareVersion -> Pointer to a the firmware version structure
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetCameraSetup(void* ph, unsigned short *wType, unsigned long *dwSetup, unsigned short *wLen);
// Gets the camera setup structure (see camera specific structures)
// Not applicable to all cameras.
// See sc2_defs.h for valid flags: -- Defines for Get / Set Camera Setup
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wType -> Pointer to a word to get the actual type (Can be NULL to query wLen).
//     DWORD* dwSetup -> Pointer to a dword array (Can be NULL to query wLen)
//     WORD *wLen -> WORD Pointer to get the length of the array
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetCameraSetup(void* ph, unsigned short wType, unsigned long *dwSetup, unsigned short wLen);
// Sets the camera setup structure (see camera specific structures)
// Camera must be reinitialized do activate new setup (Close-Open)
// Not applicable to all cameras.
// See sc2_defs.h for valid flags: -- Defines for Get / Set Camera Setup
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wType -> Word to set the actual type
//     DWORD* dwSetup -> Pointer to a dword array
//     WORD wLen -> WORD to set the length of the array
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetPowerSaveMode(void* ph, unsigned short *wMode, unsigned short *wDelayMinutes);
// Gets the camera power save mode.
// Not applicable to all cameras. Actually this is supported by pco.dimax.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wMode -> Word pointer to get the actual power save mode. (0-off,default; 1-on)
//     WORD *wDelayMinutes -> WORD to get the delay till the camera enters power save mode
//                            after main power loss. The actual switching delay is between
//                            wDelayMinutes and wDelayMinutes + 1. Possible range is 1 .. 60.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetPowerSaveMode(void* ph, unsigned short wMode, unsigned short wDelayMinutes);
// Sets the camera power save mode.
// Not applicable to all cameras. Actually this is supported by pco.dimax.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wMode -> Word to set the actual power save mode. (0-off,default; 1-on)
//     WORD wDelayMinutes -> WORD to set the delay till the camera enters power save mode
//                            after main power loss. The actual switching delay is between
//                            wDelayMinutes and wDelayMinutes + 1. Possible range is 1 .. 60.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetBatteryStatus(void* ph, unsigned short *wBatteryType, unsigned short *wBatteryLevel,
                                             unsigned short *wPowerStatus, unsigned short *wReserved, unsigned short wNumReserved);
// Gets the camera battery status.
// Not applicable to all cameras. Actually this is supported by pco.dimax.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wBatteryType -> Word pointer to get the battery type.
//                           0x0000 = no battery mounted
//                           0x0001 = nickel metal hydride type
//                           0x0002 = lithium ion type
//                           0x0003 = lithium iron phosphate type
//                           0xFFFF = unknown battery type
//     WORD *wBatteryLevel -> Word pointer to get the battery level in percent.
//     WORD *wPowerStatus  -> Word pointer to get the power status.
//                            0x0001 = power supply is available
//                            0x0002 = battery mounted and detected
//                            0x0004 = battery is charged
//                            Bits can be combined e.g. 0x0003 means that camera has
//                            a battery and is running on external power, 0x0002: camera
//                            runs on battery.

// Out: int -> Error message.

/////////////////////////////////////////////////////////////////////
/////// End: General commands ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
/////// Sensor commands /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
SC2_SDK_FUNC int WINAPI PCO_GetSensorStruct(void* ph, PCO_Sensor *strSensor);
// Gets all of the sensor data in one structure.
// In: HANDLE ph -> Handle to a previously opened camera.
//     PCO_Sensor *strSensor -> Pointer to a PCO_Sensor structure.
// Out: int -> Error message.
/* Example: see PCO_SetSensorStruct */

SC2_SDK_FUNC int WINAPI PCO_SetSensorStruct(void* ph, PCO_Sensor *strSensor);
// Sets the sensor data structure. Individual values can be set by following functions.
// This function can be used, if you have to set more than one parameter (see Example).
// In: HANDLE ph -> Handle to a previously opened camera.
//     PCO_Sensor *strSensor -> Pointer to a PCO_Sensor structure.
// Out: int -> Error message.
/* Example:
  HANDLE hCamera;
  ...
  PCO_Sensor strSensor;
  strSensor.wSize = sizeof(PCO_Sensor);
  int err = PCO_GetSensorStruct(hCamera, &strSensor);
  ...
  strSensor.wRoiX0 = 20;
  strSensor.wRoiX1 = 820;
  strSensor.wRoiY0 = 200;
  strSensor.wRoiY1 = 400;
  strSensor.wBinHorz = 2;                // Change horizontal binning
  strSensor.wBinVert = 2;                // Change vertical binning
  ...
  int err = PCO_SetSensorStruct(hCamera, &strSensor);
  ...
*/

SC2_SDK_FUNC int WINAPI PCO_GetCameraDescription(void* ph, PCO_Description *strDescription);
// Gets the camera description data structure.
// In: HANDLE ph -> Handle to a previously opened camera.
//     PCO_Description *strDescription -> Pointer to a PCO_Description structure.
// Out: int -> Error message.
/* Example: see PCO_GetSensorStruct in PCO_SetSensorStruct */

SC2_SDK_FUNC int WINAPI PCO_GetCameraDescriptionEx(void* ph, PCO_DescriptionEx *strDescription, unsigned short wType);
// Gets the camera description data structure.
// Not applicable to all cameras. Check Description
// In: HANDLE ph -> Handle to a previously opened camera.
//     PCO_DescriptionEx *strDescription -> Pointer to a PCO_Description structure.
//     WORD wType -> Type of descriptor: 0 -> standard (must have); 1 -> second (check standard)
// Out: int -> Error message.
/* Example: see PCO_GetSensorStruct in PCO_SetSensorStruct */

SC2_SDK_FUNC int WINAPI PCO_GetSensorFormat(void* ph, unsigned short* wSensor);
// Gets the sensor format.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wSensor -> Pointer to a WORD variable to receive the sensor format.
// Out: int -> Error message.
/* Example:
  HANDLE hCamera;
  ...
  WORD wSensorFormat;
  int err = PCO_GetSensorFormat(hCamera, &wSensorFormat);
  ...
*/

SC2_SDK_FUNC int WINAPI PCO_SetSensorFormat(void* ph, unsigned short wSensor);
// Sets the sensor format.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wSensor -> WORD variable which holds the sensor format.
// Out: int -> Error message.
/* Example:
  HANDLE hCamera;
  ...
  WORD wSensorFormat;
  wSensorFormat = 1;                   // 0: normal, 1: extended
  int err = PCO_SetSensorFormat(hCamera, wSensorFormat);
  ...
*/

SC2_SDK_FUNC int WINAPI PCO_GetSizes(void* ph,
                            unsigned short *wXResAct, // Actual X Resolution
                            unsigned short *wYResAct, // Actual Y Resolution
                            unsigned short *wXResMax, // Maximum X Resolution
                            unsigned short *wYResMax); // Maximum Y Resolution
// Gets the actual and maximum sizes of the camera. The maximum y value includes the
// size of a double shutter image.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wXResAct -> Pointer to a WORD variable to receive the actual X resolution.
//     WORD *wYResAct -> Pointer to a WORD variable to receive the actual Y resolution.
//     WORD *wXResMax -> Pointer to a WORD variable to receive the maximal X resolution.
//     WORD *wXResMax -> Pointer to a WORD variable to receive the maximal Y resolution.
// Out: int -> Error message.
/* Example:
  HANDLE hCamera;
  ...
  WORD wXResAct;                       // Actual X Resolution
  WORD wYResAct;                       // Actual Y Resolution
  WORD wXResMax;                       // Maximum X Resolution
  WORD wYResMax;                       // Maximum Y Resolution
  int err = PCO_GetSizes(hCamera, &wXResAct, &wYResAct, &wXResMax, &wYResMax);
  ...
*/

SC2_SDK_FUNC int WINAPI PCO_GetROI(void* ph,
                            unsigned short *wRoiX0, // Roi upper left x
                            unsigned short *wRoiY0, // Roi upper left y
                            unsigned short *wRoiX1, // Roi lower right x
                            unsigned short *wRoiY1);// Roi lower right y
// Gets the region of interest of the camera. X0, Y0 start at 1. X1, Y1 end with max. sensor size.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wRoiX0 -> Pointer to a WORD variable to receive the x value for the upper left corner.
//     WORD *wRoiY0 -> Pointer to a WORD variable to receive the y value for the upper left corner.
//     WORD *wRoiX1 -> Pointer to a WORD variable to receive the x value for the lower right corner.
//     WORD *wRoiY0 -> Pointer to a WORD variable to receive the y value for the lower right corner.
//      x0,y0----------|
//      |     ROI      |
//      ---------------x1,y1
// Out: int -> Error message.
/* Example: see PCO_GetSizes */

SC2_SDK_FUNC int WINAPI PCO_SetROI(void* ph,
                            unsigned short wRoiX0, // Roi upper left x
                            unsigned short wRoiY0, // Roi upper left y
                            unsigned short wRoiX1, // Roi lower right x
                            unsigned short wRoiY1);// Roi lower right y
// Gets the region of interest of the camera. X0, Y0 start at 1. X1, Y1 end with max. sensor size.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wRoiX0 -> WORD variable to hold the x value for the upper left corner.
//     WORD wRoiY0 -> WORD variable to hold the y value for the upper left corner.
//     WORD wRoiX1 -> WORD variable to hold the x value for the lower right corner.
//     WORD wRoiY0 -> WORD variable to hold the y value for the lower right corner.
//      x0,y0----------|
//      |     ROI      |
//      ---------------x1,y1
// Out: int -> Error message.
/* Example:
  HANDLE hCamera;
  ...
  WORD wRoiX0;                         // x value for the upper left corner.
  WORD wRoiY0;                         // y value for the upper left corner.
  WORD wRoiX1;                         // x value for the lower right corner.
  WORD wRoiY0;                         // y value for the lower right corner.

  wRoiX0 = 20;  wRoiX1 = 820;  wRoiY0 = 200;  wRoiY1 = 400;
  int err = PCO_SetROI(hCamera, wRoiX0, wRoiY0, wRoiX1, wRoiY1);
  ...
*/

SC2_SDK_FUNC int WINAPI PCO_GetBinning(void* ph,
                                unsigned short *wBinHorz, // Binning horz. (x)
                                unsigned short *wBinVert);// Binning vert. (y)
// Gets the binning values of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wBinHorz -> Pointer to a WORD variable to hold the horizontal binning value.
//     WORD *wBinVert -> Pointer to a WORD variable to hold the vertikal binning value.
// Out: int -> Error message.
/* Example: PCO_GetSizes */

SC2_SDK_FUNC int WINAPI PCO_SetBinning(void* ph,
                                unsigned short wBinHorz, // Binning horz. (x)
                                unsigned short wBinVert);// Binning vert. (y)
// Sets the binning values of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wBinHorz -> WORD variable to hold the horizontal binning value.
//     WORD wBinVert -> WORD variable to hold the vertikal binning value.
// Out: int -> Error message.
/* Example: PCO_SetROI */

SC2_SDK_FUNC int WINAPI PCO_GetPixelRate(void* ph,
                                  unsigned long *dwPixelRate); // Pixelrate
// Gets the pixel rate of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD *dwPixelRate -> Pointer to a DWORD variable to receive the pixelrate.
// Out: int -> Error message.
/* Example:
  HANDLE hCamera;
  ...
  DWORD dwPixelRate;                   // PixelRate

  int err = PCO_GetPixelRate(hCamera, &dwPixelRate);
  ...
*/

SC2_SDK_FUNC int WINAPI PCO_SetPixelRate(void* ph,
                                  unsigned long dwPixelRate); // Pixelrate
// Sets the pixel rate of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD dwPixelRate -> DWORD variable to hold the pixelrate.
// Out: int -> Error message.
/* Example:
  HANDLE hCamera;
  ...
  DWORD dwPixelRate;

  dwPixelRate = 20000000;              // PixelRate in Hz
  int err = PCO_SetPixelRate(hCamera, dwPixelRate);
  ...
*/

SC2_SDK_FUNC int WINAPI PCO_GetConversionFactor(void* ph,
                                 unsigned short *wConvFact); // Conversion Factor (Gain)
// Gets the conversion factor of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wConvFact -> Pointer to a WORD variable to receive the conversin factor.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetConversionFactor(void* ph,
                                 unsigned short wConvFact); // Conversion Factor (Gain)
// Sets the conversion factor of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wConvFact -> WORD variable to hold the conversin factor.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetDoubleImageMode(void* ph,
                                        unsigned short *wDoubleImage); // DoubleShutter Mode
// Gets the double image mode of the camera.
// Not applicable to all cameras. Check Description
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wDoubleImage -> Pointer to a WORD variable to receive the double image mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetDoubleImageMode(void* ph,
                                        unsigned short wDoubleImage); // DoubleShutter Mode
// Sets the double image mode of the camera, if available.
// Not applicable to all cameras. Check Description
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wDoubleImage -> WORD variable to hold the double image mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetADCOperation(void* ph,
                                     unsigned short *wADCOperation); // ADC Operation
// Gets the adc operation mode of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wADCOperation -> Pointer to a WORD variable to receive the adc operation mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetADCOperation(void* ph,
                                     unsigned short wADCOperation); // ADC Operation
// Sets the adc operation mode of the camera, if available.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wADCOperation -> WORD variable to hold the adc operation mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetIRSensitivity(void* ph,
                               unsigned short *wIR); // IR Sensitivity
// Gets the IR Sensitivity mode of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wIR -> Pointer to a WORD variable to receive the IR Sensitivity mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetIRSensitivity(void* ph,
                               unsigned short wIR); // IR Sensitivity
// Sets the IR Sensitivity mode of the camera, if available.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wIR -> WORD variable to hold the IR Sensitivity mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetCoolingSetpointTemperature(void* ph,
                                short *sCoolSet); // Cooling setpoint
// Gets the cooling setpoint temperature of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     SHORT *sCoolSet -> Pointer to a SHORT variable to receive the cooling setpoint temperature.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetCoolingSetpointTemperature(void* ph,
                                short sCoolSet); // Cooling setpoint
// Sets the cooling setpoint temperature of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     SHORT sCoolSet -> SHORT variable to hold the cooling setpoint temperature.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetOffsetMode(void* ph,
                                   unsigned short *wOffsetRegulation); // Offset mode
// Gets the offset mode of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wOffsetRegulation -> Pointer to a WORD variable to receive the offset mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetOffsetMode(void* ph,
                                   unsigned short wOffsetRegulation); // Offset mode
// Sets the offset mode of the camera, if available.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wOffsetRegulation -> WORD variable to hold the offset mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetNoiseFilterMode(void* ph,
                                   unsigned short *wNoiseFilterMode); // 
// Gets the noise filter mode of the camera, if available.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wNoiseFilterMode -> Pointer to a WORD variable to receive the noise filter mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetNoiseFilterMode(void* ph,
                                   unsigned short wNoiseFilterMode); // 
// Sets the noise filter mode of the camera, if available.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wNoiseFilterMode -> WORD variable to hold the noise filter mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetHWIOSignalCount(void* ph, unsigned short *wNumSignals);
// Gets the number of available hw signals
// Not applicable to all cameras. Check Description
// In: HANDLE ph -> Handle to a proviously opened camera.
//     WORD* wNumSignals -> WORD variable to get the number of signals
// Out: int -> Error message

SC2_SDK_FUNC int WINAPI PCO_GetHWIOSignalDescriptor(void* ph, unsigned short wSignalNum, PCO_Single_Signal_Desc *pstrSignal);
// Gets the signal descriptor of the requested signal number
// Not applicable to all cameras. Check Description
// In: HANDLE ph -> Handle to a proviously opened camera.
//     WORD wSignalNum -> WORD variable to query the signal
//     SIGNAL_DESC *ptrSignal -> Pointer to a SIGNAL_DESC structure to get the
//                               signal description
// Out: int -> Error message

SC2_SDK_FUNC int WINAPI PCO_GetColorCorrectionMatrix(void* ph, double* pdMatrix);
// Gets the color multiplier matrix to normalise the color values of a color camera to 6500k.
// This option is only available with a pco.dimax
// In: HANDLE ph -> Handle to a proviously opened camera.
//     double *pdMatrix -> Array pointer to a double array containing
//                         9 double to receive the color matrix coefficients
// Out: int -> Error message

SC2_SDK_FUNC int WINAPI PCO_GetBayerMultiplier(void* ph, unsigned short *wMode, unsigned short *wMul);
// Requests the Bayer multipliers. The Bayer multipliers are used by cameras with color sensor in
// order to compensate the color response of the sensor and the optical setup. Thus when exposed to
// white light the R Gr Gb B pixels will ideally show the same amplitude.
// This option is only available with a pco.dimax
// In: HANDLE ph -> Handle to a proviously opened camera.
//     WORD *wMode -> Mode = 0x0001: The returned values are changed, but not yet saved.
//                    Mode = 0x0002: The returned values are saved.
//     WORD *wMul -> Pointer to an array of four WORD;
//                   Red/GreenRed/GreenBlue/Blue Multiplier: Number from 0 to 3999, where 1000
//                   corresponds to multiplier of 1.0 (leave values unchanged).
//                   Element 0 is the same as in the color descriptor. See wColorPatternDESC
//                   in PCO_Description
// Out: int -> Error message

SC2_SDK_FUNC int WINAPI PCO_SetBayerMultiplier(void* ph, unsigned short wMode, unsigned short *wMul);
// Sets the RGB multipliers. The Bayer multipliers are used by cameras with color sensor in
// order to compensate the color response of the sensor and the optical setup. Thus when exposed to
// white light the R Gr Gb B pixels will ideally show the same amplitude.
// This option is only available with a pco.dimax
// In: HANDLE ph -> Handle to a proviously opened camera.
//     WORD *wMode -> Mode = 0x0001: Set new values immediately but do not save.
//                    Mode = 0x0002: Save values and set immediately.
//     WORD *wMul -> Pointer to an array of four WORD;
//                   Red/GreenRed/GreenBlue/Blue Multiplier: Number from 0 to 3999, where 1000
//                   corresponds to multiplier of 1.0 (leave values unchanged).
//                   Element 0 is the same as in the color descriptor. See wColorPatternDESC
//                   in PCO_Description
// Out: int -> Error message

SC2_SDK_FUNC int WINAPI PCO_GetDSNUAdjustMode(void* ph,
                                              unsigned short* wDSNUAdjustMode,
                                              unsigned short* wReserved);
// Gets the camera internal DSNU adjustment mode. Dimax only!
// In: HANDLE ph -> Handle to a proviously opened camera.
//     WORD *wDSNUAdjustMode -> Mode = 0: no DSNU correction.
//                             Mode = 1: automatic DSNU correction.
//                             Mode = 2: manual DSNU correction.
//     WORD *wReserved -> Pointer to a WORD to receive ...zero?
// Out: int -> Error message

SC2_SDK_FUNC int WINAPI PCO_SetDSNUAdjustMode(void* ph,
                                              unsigned short wDSNUAdjustMode,
                                              unsigned short wReserved);
// Sets the camera internal DSNU adjustment mode. Dimax only!
// In: HANDLE ph -> Handle to a proviously opened camera.
//     WORD wDSNUAdjustMode -> Mode = 0: no DSNU correction.
//                             Mode = 1: automatic DSNU correction.
//                             Mode = 2: manual DSNU correction.
//     WORD wReserved -> set to zero!
// Out: int -> Error message

SC2_SDK_FUNC int WINAPI PCO_InitDSNUAdjustment(void* ph,
                                               unsigned short wDSNUAdjustMode,
                                               unsigned short wReserved);
// Starts the camera internal DSNU adjustment in case it is set to manually. Dimax only!
// In: HANDLE ph -> Handle to a proviously opened camera.
//     WORD wDSNUAdjustMode -> Mode = 0: no DSNU correction.
//                             Mode = 1: automatic DSNU correction.
//                             Mode = 2: manual DSNU correction.
//     WORD wReserved -> set to zero!
// Out: int -> Error message

SC2_SDK_FUNC int WINAPI PCO_GetCDIMode(void* ph,
                                       unsigned short *wCDIMode); // 
// Gets the correlated double image mode of the camera, if available.
// Only available with a dimax
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wCDIMode -> Pointer to a WORD variable to receive the correlated double image mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetCDIMode(void* ph,
                                       unsigned short wCDIMode); // 
// Sets the correlated double image mode of the camera, if available.
// Only available with a dimax
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wCDIMode -> WORD variable to set the correlated double image mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetLookupTableInfo(void* ph,
  unsigned short        wLUTNum,                 // Number of LUT to query
  unsigned short        *wNumberOfLuts,          // Number of LUTs which can be queried
  char        *Description,            // e.g. "HD/SDI 12 to 10"
  unsigned short        wDescLen,                // length of the description string buffer
  unsigned short        *wIdentifier,            // define loadable LUTs, range 0x0001 to 0xFFFF
  unsigned char         *bInputWidth,            // maximal Input in Bits
  unsigned char         *bOutputWidth,           // maximal Output in Bits
  unsigned short        *wFormat);               // accepted data structures (see defines)) // Correlated Double Image mode
// Gets infos about lookup tables in the camera, if available.
// Only available with a pco.edge
// In: HANDLE ph -> Handle to a previously opened camera.
//     see above.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetActiveLookupTable(void* ph,
  unsigned short        *wIdentifier,            // define LUT to be activated, 0x0000 for no LUT
  unsigned short        *wParameter);            // optional parameter
// Gets the active lookup tables in the camera, if available.
// Only available with a pco.edge
// In: HANDLE ph -> Handle to a previously opened camera.
//     see above.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetActiveLookupTable(void* ph,
  unsigned short        *wIdentifier,            // define LUT to be activated, 0x0000 for no LUT
  unsigned short        *wParameter);            // optional parameter
// Sets the active lookup tables in the camera, if available.
// Only available with a pco.edge
// In: HANDLE ph -> Handle to a previously opened camera.
//     see above.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_LoadLookupTable(void* ph,
  unsigned short        *wIdentifier,            // define LUT to be loaded
  unsigned short        *wPacketNum,             // for loading LUT in several steps
  unsigned short        *wFormat,                // data structure in *bData (see defines)
  unsigned short        *wLength,                // valid number of bytes within this call
  unsigned char        *bData);                 // data
// Loads a lookup tables to the camera, if available.
// Only available with a pco.edge
// In: HANDLE ph -> Handle to a previously opened camera.
//     see above.
// Out: int -> Error message.

/////////////////////////////////////////////////////////////////////
/////// End: Sensor commands ////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
/////// Timing commands /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
SC2_SDK_FUNC int WINAPI PCO_GetTimingStruct(void* ph, PCO_Timing *strTiming);
// Gets all of the timing data in one structure.
// In: HANDLE ph -> Handle to a previously opened camera.
//     PCO_Timing *strTiming -> Pointer to a PCO_Timing structure.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetTimingStruct(void* ph, PCO_Timing *strTiming);
// Sets all of the timing data in one structure.
// In: HANDLE ph -> Handle to a previously opened camera.
//     PCO_Timing strTiming -> PCO_Timing structure.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetDelayExposureTime(void* ph, // Timebase: 0-ns; 1-us; 2-ms 
                             unsigned long* dwDelay,
                             unsigned long* dwExposure,
                             unsigned short* wTimeBaseDelay,
                             unsigned short* wTimeBaseExposure);
// Gets the exposure and delay time and the time bases of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD* dwDelay -> Pointer to a DWORD variable to receive the exposure time.
//     DWORD* dwExposure -> Pointer to a DWORD variable to receive the delay time.
//     WORD* wTimeBaseDelay -> Pointer to a WORD variable to receive the exp. timebase.
//     WORD* wTimeBaseExposure -> Pointer to a WORD variable to receive the del. timebase.
// Timebase: 0 -> value is in ns: exp. time of 100 means 0.0000001s.
//           1 -> value is in us: exp. time of 100 means 0.0001s.
//           2 -> value is in ms: exp. time of 100 means 0.1s.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetDelayExposureTime(void* ph, // Timebase: 0-ns; 1-us; 2-ms  
                             unsigned long dwDelay,
                             unsigned long dwExposure,
                             unsigned short wTimeBaseDelay,
                             unsigned short wTimeBaseExposure);
// Sets the exposure and delay time and the time bases of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD dwDelay -> DWORD variable to hold the exposure time.
//     DWORD dwExposure -> DWORD variable to hold the delay time.
//     WORD wTimeBaseDelay -> WORD variable to hold the exp. timebase.
//     WORD wTimeBaseExposure -> WORD variable to hold the del. timebase.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetDelayExposureTimeTable(void* ph, // Timebase: 0-ns; 1-us; 2-ms 
                                  unsigned long* dwDelay,
                                  unsigned long* dwExposure,
                                  unsigned short* wTimeBaseDelay,
                                  unsigned short* wTimeBaseExposure,
                                  unsigned short wCount);
// Gets the exposure and delay time table and the time bases of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD* dwDelay -> Pointer to a DWORD array to receive the exposure times.
//     DWORD* dwExposure -> Pointer to a DWORD array to receive the delay times.
//     WORD* wTimeBaseDelay -> Pointer to a WORD variable to receive the exp. timebase.
//     WORD* wTimeBaseExposure -> Pointer to a WORD variable to receive the del. timebase.
// Out: int -> Error message.
/* Example: see PCO_SetDelayExposureTimeTable */

SC2_SDK_FUNC int WINAPI PCO_SetDelayExposureTimeTable(void* ph, // Timebase: 0-ns; 1-us; 2-ms 
                                  unsigned long* dwDelay,
                                  unsigned long* dwExposure,
                                  unsigned short wTimeBaseDelay,
                                  unsigned short wTimeBaseExposure,
                                  unsigned short wCount);
// Sets the exposure and delay time table and the time bases of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD* dwDelay -> Pointer to a DWORD array to hold the exposure times.
//     DWORD* dwExposure -> Pointer to a DWORD array to hold the delay times.
//     WORD wTimeBaseDelay -> WORD variable to hold the exp. timebase.
//     WORD wTimeBaseExposure -> WORD variable to hold the del. timebase.
// Out: int -> Error message.
/* Example:
#define MAXTIMEPAIRS 16 // maximum count of delay and exposure pairs
  HANDLE hHandleCam;
  ...
  DWORD dwDelay[MAXTIMEPAIRS], dwExposure[MAXTIMEPAIRS];
  WORD wTimeBaseDelay, wTimeBaseExposure;
  int err = PCO_GetDelayExposureTimeTable(hHandleCam, &dwDelay[0], &dwExposure[0],
                                          &wTimeBaseDelay, &wTimeBaseExposure, MAXTIMEPAIRS);
  dwDelay[0] = 100;
  dwExposure[0] = 10;
  dwDelay[1] += 200;
  dwExposure[1] += 10;                 // This changes only the first two pairs.
  int err = PCO_SetDelayExposureTimeTable(hHandleCam, &dwDelay[0], &dwExposure[0],
                                          wTimeBaseDelay, wTimeBaseExposure, 2);
  ...
*/

SC2_SDK_FUNC int WINAPI PCO_GetTriggerMode(void* ph, unsigned short* wTriggerMode);
// Gets the trigger mode of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wTriggerMode -> Pointer to a WORD variable to receive the triggermode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetTriggerMode(void* ph, unsigned short wTriggerMode);
// Sets the trigger mode of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wTriggerMode -> WORD variable to hold the triggermode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_ForceTrigger(void* ph, unsigned short *wTriggered);
// Forces a trigger to the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wTriggered -> Pointer to a WORD variable to receive whether
//                         a trigger occured or not.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetCameraBusyStatus(void* ph, unsigned short* wCameraBusyState);
// Gets the busy state of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wCameraBusyState -> Pointer to a WORD variable to receive the busy state.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetPowerDownMode(void* ph, unsigned short* wPowerDownMode);
// Gets the power down mode of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wPowerDownMode -> Pointer to a WORD variable to receive the power down mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetPowerDownMode(void* ph, unsigned short wPowerDownMode);
// Sets the power down mode of the camera, if available.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wPowerDownMode -> WORD variable to hold the power down mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetUserPowerDownTime(void* ph, unsigned long* dwPowerDownTime);
// Gets the power down time of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wPowerDownTime -> Pointer to a WORD variable to receive the power down time.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetUserPowerDownTime(void* ph, unsigned long dwPowerDownTime);
// Sets the power down time of the camera, if available.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wPowerDownTime -> Pointer to a WORD variable to receive the power down time.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetExpTrigSignalStatus(void* ph, unsigned short* wExpTrgSignal);
// Gets the exposure trigger signal state of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wExpTrgSignal -> Pointer to a WORD variable to receive the
//                            exposure trigger signal state.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetCOCRuntime(void* ph, unsigned long* dwTime_s, unsigned long* dwTime_us);
// Gets the exposure trigger signal state of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD* dwTime_s -> Pointer to a DWORD variable to receive the
//                        time part in seconds of the COC.
//     DWORD* dwTime_us -> Pointer to a DWORD variable to receive the
//                         time part in microseconds of the COC.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetFPSExposureMode(void* ph, unsigned short* wFPSExposureMode, unsigned long* dwFPSExposureTime);
// Gets the FPS exposure mode and the corresponding exposure time.
// This option is only available with pco.1200hs
// In: HANDLE ph -> Handle to a proviously opened camera.
//     WORD* wFPSExposureMode -> Pointer to a WORD variable to receive the FPS-exposure-mode.
//     DWORD* dwFPSExposureTime -> Pointer to a DWORD variable to receive the FPS exposure time.
// Out: int -> Error message

SC2_SDK_FUNC int WINAPI PCO_SetFPSExposureMode(void* ph, unsigned short wFPSExposureMode, unsigned long* dwFPSExposureTime);
// Sets the FPS exposure mode and gets the corresponding exposure time.
// This option is only available with pco.1200hs
// In: HANDLE ph -> Handle to a proviously opened camera.
//     WORD wFPSExposureMode -> WORD variable to hold the FPS-exposure-mode.
//     DWORD* dwFPSExposureTime -> Pointer to a DWORD variable to receive the FPS exposure time.
// Out: int -> Error message
SC2_SDK_FUNC int WINAPI PCO_GetModulationMode(void* ph, unsigned short *wModulationMode, unsigned long *dwPeriodicalTime,
                                              unsigned short *wTimebasePeriodical, unsigned long *dwNumberOfExposures,
                                              long *lMonitorOffset);
// Gets the modulation mode and neccessary parameters
// This option is only available with a modulation enabled camera
// In: HANDLE ph -> Handle to a proviously opened camera.
//     WORD *wModulationMode -> Pointer to a WORD variable to receive the modulation mode
//     DWORD *dwPeriodicalTime -> Pointer to a DWORD variable to receive the periodical time
//     WORD *wTimebasePeriodical -> Pointer to a WORD variable to receive the time base of pt
//     DWORD *dwNumberOfExposures -> Pointer to a DWORD variable to receive the number of exposures
//     LONG *lMonitorOffset -> Pointer to a signed DWORD variable to receive the monitor offset
// Out: int -> Error message
SC2_SDK_FUNC int WINAPI PCO_SetModulationMode(void* ph, unsigned short wModulationMode, unsigned long dwPeriodicalTime,
                                              unsigned short wTimebasePeriodical, unsigned long dwNumberOfExposures,
                                              long lMonitorOffset);
// Sets the modulation mode and neccessary parameters
// This option is only available with a modulation enabled camera
// In: HANDLE ph -> Handle to a proviously opened camera.
//     WORD wModulationMode -> WORD variable to hold the modulation mode
//     DWORD dwPeriodicalTime -> DWORD variable to hold the periodical time
//     WORD wTimebasePeriodical -> WORD variable to hold the time base of pt
//     DWORD dwNumberOfExposures -> DWORD variable to hold the number of exposures
//     LONG lMonitorOffset -> DWORD variable to hold the monitor offset
// Out: int -> Error message

SC2_SDK_FUNC int WINAPI PCO_GetFrameRate(void* ph, unsigned short* wFrameRateStatus, unsigned long* dwFrameRate, unsigned long* dwFrameRateExposure);
// Gets the frame rate status, rate and exposure
// This option is only available with a pco.dimax
// In: HANDLE ph -> Handle to a proviously opened camera.
//     WORD* wFrameRateStatus -> WORD variable to receive the status
//           0x0000: Settings consistent, all conditions met
//           0x0001: Framerate trimmed, framerate was limited by readout time
//           0x0002: Framerate trimmed, framerate was limited by exposure time
//           0x0004: Exposure time trimmed, exposure time cut to frame time
//     DWORD* dwFrameRate -> DWORD variable to receive the actual frame rate
//     DWORD* dwFrameRateExposure -> DWORD variable to receive the actual exposure time (in ns)
// Out: int -> Error message

SC2_SDK_FUNC int WINAPI PCO_SetFrameRate(void* ph, unsigned short* wFrameRateStatus, unsigned short wFrameRateMode, unsigned long* dwFrameRate, unsigned long* dwFrameRateExposure);
// Sets the frame rate mode, rate and exposure
// This option is only available with a pco.dimax
// In: HANDLE ph -> Handle to a proviously opened camera.
//     WORD* wFrameRateStatus -> WORD variable to receive the status
//           0x0000: Settings consistent, all conditions met
//           0x0001: Framerate trimmed, framerate was limited by readout time
//           0x0002: Framerate trimmed, framerate was limited by exposure time
//           0x0004: Exposure time trimmed, exposure time cut to frame time
//     WORD wFrameRateMode -> WORD variable to set the frame rate mode
//           0x0000: auto mode (camera decides which parameter will be trimmed)
//           0x0001: Framerate has priority, (exposure time will be trimmed)
//           0x0002: Exposure time has priority, (framerate will be trimmed)
//           0x0003: Strict, function shall return with error if values are not possible.
//     DWORD* dwFrameRate -> DWORD variable to receive the actual frame rate
//     DWORD* dwFrameRateExposure -> DWORD variable to receive the actual exposure time (in ns)
// Out: int -> Error message


SC2_SDK_FUNC int WINAPI PCO_GetHWIOSignal(void* ph, unsigned short wSignalNum, PCO_Signal *pstrSignal);
// Gets the signal options of the requested signal number
// This option is only available with a pco.dimax
// In: HANDLE ph -> Handle to a proviously opened camera.
//     WORD wSignalNum -> WORD variable to query the signal
//     PCO_Signal *ptrSignal -> Pointer to a signal structure
// Out: int -> Error message

SC2_SDK_FUNC int WINAPI PCO_SetHWIOSignal(void* ph, unsigned short wSignalNum, PCO_Signal *pstrSignal);
// Sets the signal options of the requested signal number
// This option is only available with a pco.dimax
// In: HANDLE ph -> Handle to a proviously opened camera.
//     WORD wSignalNum -> WORD variable to query the signal
//     PCO_Signal *ptrSignal -> Pointer to a signal structure
// Out: int -> Error message

SC2_SDK_FUNC int WINAPI PCO_GetImageTiming(void* ph, PCO_ImageTiming *pstrImageTiming);
// Gets the timing of one image, including trigger delay, trigger jitter, 
// This option is only available with a pco.dimax
// In: HANDLE ph -> Handle to a proviously opened camera.
//     PCO_ImageTiming *pstrImageTiming -> Pointer to a image timing structure
// Out: int -> Error message

SC2_SDK_FUNC int WINAPI PCO_GetCameraSynchMode(void* ph, unsigned short *wCameraSynchMode);
// Gets the camera synch mode of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wCameraSynchMode -> Pointer to a WORD variable to receive the synch mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetCameraSynchMode(void* ph, unsigned short wCameraSynchMode);
// Sets the camera synch mode of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wCameraSynchMode -> WORD variable to set the synch mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetFastTimingMode(void* hCam, unsigned short* wFastTimingMode);
// Gets the fast timing mode of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wFastTimingMode -> Pointer to a WORD variable to receive the fast timing mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetFastTimingMode(void* hCam, unsigned short wFastTimingMode);
// Sets the fast timing mode of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wFastTimingMode -> WORD variable to set the fast timing mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetSensorSignalStatus(void* hCam, unsigned long* dwStatus, unsigned long* dwImageCount, unsigned long* dwReserved1, unsigned long *dwReserved2);
// Gets the signal state of the camera sensor. The signals must not be deemed to be a realtime
// response of the sensor, since the command path adds a system dependent delay. Sending a command
// and getting the camera response lasts about 2ms (+/- 1ms; for 'simple' commands). In case
// you need a closer synchronisation use hardware signals.
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD* dwStatus -> DWORD pointer to receive the status flags of the sensor (can be NULL).
//                        Bit0: SIGNAL_STATE_BUSY  0x0001
//                        Bit1: SIGNAL_STATE_IDLE  0x0002
//                        Bit2: SIGNAL_STATE_EXP   0x0004
//                        Bit3: SIGNAL_STATE_READ  0x0008
//     DWORD* dwImageCount -> DWORD pointer to receive the # of the last finished image(can be NULL).
//     DWORD* dwReserved -> DWORD pointer for future use (can be NULL).
// Out: int -> Error message.

/////////////////////////////////////////////////////////////////////
/////// End: Timing commands ////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
/////// Storage commands ////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
SC2_SDK_FUNC int WINAPI PCO_GetStorageStruct(void* ph, PCO_Storage *strStorage);
// Gets all of the storage data in one structure.
// In: HANDLE ph -> Handle to a previously opened camera.
//     PCO_Recording *strRecording -> Pointer to a PCO_Recording structure.
// Out: int -> Error message.


SC2_SDK_FUNC int WINAPI PCO_SetStorageStruct(void* ph, PCO_Storage *strStorage);
// Sets all of the storage data in one structure.
// In: HANDLE ph -> Handle to a previously opened camera.
//     PCO_Recording *strRecording -> Pointer to a PCO_Recording structure.
// Out: int -> Error message.


SC2_SDK_FUNC int WINAPI PCO_GetCameraRamSize(void* ph, unsigned long* dwRamSize, unsigned short* wPageSize);
// Gets the ram and pagesize of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD* dwRamSize -> Pointer to a DWORD variable to receive the ramsize in pages.
//     DWORD* dwPageSize -> Pointer to a DWORD variable to receive the pagesize in bytes.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetCameraRamSegmentSize(void* ph, unsigned long* dwRamSegSize);
// Gets the segmentsizes of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD* dwRamSegSize -> Pointer to a DWORD array to receive the ramsegmentsize in pages.
// Out: int -> Error message.
/* Example: see PCO_SetCameraRamSegmentSize */

SC2_SDK_FUNC int WINAPI PCO_SetCameraRamSegmentSize(void* ph, unsigned long* dwRamSegSize);
// Gets the segmentsizes of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD* dwRamSegSize -> Pointer to a DWORD array to receive the ramsegmentsize in pages.
// Out: int -> Error message.
/* Example:
  #define MAXSEGMENTS 4
  HANDLE hHandleCam;
  ...
  DWORD dwRamSegSize[MAXSEGMENTS];
  int err = PCO_GetCameraRamSegmentSize(hHandleCam, &dwRamSegSize[0]);
  dwRamSegSize[0] = dwRamSegSize[0] + dwRamSegSize[1] + dwRamSegSize[2] + dwRamSegSize[3];
  dwRamSegSize[1] = dwRamSegSize[2] = dwRamSegSize[3] = 0;// Set all memory to segment 1.
  // Our camera has got 4 segments (up to now). They start with Segment 1, up to 4.
  // In programming languages every array starts with index 0! So, segment number 1
  // has the index 0, seg. 2 has 1, 3 has 2 and 4 has 3.
  err = PCO_SetCameraRamSegmentSize(hHandleCam, &dwRamSegSize[0]);
  ...
*/

SC2_SDK_FUNC int WINAPI PCO_ClearRamSegment(void* ph);
// Clears (deletes all images) of the actieve ram segment of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetActiveRamSegment(void* ph, unsigned short* wActSeg);
// Gets the active ram segment of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wActSeg -> Pointer to a WORD variable to receive the actual segment.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetActiveRamSegment(void* ph, unsigned short wActSeg);
// Sets the active ram segment of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wActSeg -> WORD variable to hold the actual segment.
// Out: int -> Error message.

/////////////////////////////////////////////////////////////////////
/////// End: Storage commands ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
/////// Recording commands //////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
SC2_SDK_FUNC int WINAPI PCO_GetRecordingStruct(void* ph, PCO_Recording *strRecording);
// Gets all of the recording data in one structure.
// In: HANDLE ph -> Handle to a previously opened camera.
//     PCO_Recording *strRecording -> Pointer to a PCO_Recording structure.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetRecordingStruct(void* ph, PCO_Recording *strRecording);
// Sets all of the recording data in one structure.
// In: HANDLE ph -> Handle to a previously opened camera.
//     PCO_Recording *strRecording -> Pointer to a PCO_Recording structure.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetStorageMode(void* ph, unsigned short* wStorageMode);
// Gets the storage mode of the camera. 0: recorder, 1: fifo
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wStorageMode -> Pointer to a WORD variable to receive the storage mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetStorageMode(void* ph, unsigned short wStorageMode);
// Sets the storage mode of the camera. 0: recorder, 1: fifo
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wStorageMode -> WORD variable to hold the storage mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetRecorderSubmode(void* ph, unsigned short* wRecSubmode);
// Gets the recorder sub mode of the camera. 0: sequence, 1: ring buffer
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wRecSubmode -> Pointer to a WORD variable to receive the recorder sub mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetRecorderSubmode(void* ph, unsigned short wRecSubmode);
// Sets the recorder sub mode of the camera. 0: sequence, 1: ring buffer
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wRecSubmode -> WORD variable to hold the recorder sub mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetRecordingState(void* ph, unsigned short* wRecState);
// Gets the recording state of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wRecState -> Pointer to a WORD variable to receive the recording state.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetRecordingState(void* ph, unsigned short wRecState);
// Sets the recording state of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wRecState -> WORD variable to hold the recording state.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_ArmCamera(void* ph);
// Sets all previously set data to the camera operation code. This command prepares the
// camera for recording images. This is the last command before setting the recording
// state. If you change any settings after this command, you have to send this command again.
// If you don't arm your camera after changing settings, the camera will run with the last
// 'armed' settings and in this case you do not know in what way your camera is acquiring images.
// In: HANDLE ph -> Handle to a previously opened camera.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetAcquireMode(void* ph, unsigned short* wAcquMode);
// Gets the acquire mode of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wAcquMode -> Pointer to a WORD variable to receive the acquire mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetAcquireMode(void* ph, unsigned short wAcquMode);
// Sets the acquire mode of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wAcquMode -> WORD variable to hold the acquire mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetAcqEnblSignalStatus(void* ph, unsigned short* wAcquEnableState);
// Gets the acquire enable signal status.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wAcquEnableState -> Pointer to a WORD variable to receive the acquire
//                               enable signal status.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetDateTime(void* ph,
                                        unsigned char ucDay,
                                        unsigned char ucMonth,
                                        unsigned short wYear,
                                        unsigned short wHour,
                                        unsigned char ucMin,
                                        unsigned char ucSec);
// Sets the time and date to the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     BYTE ucDay -> Day of month (1-31).
//     BYTE ucMonth -> Month of the year (1-12).
//     WORD wYear -> Year with four digits: 2003
//     WORD wHour -> Hour of day in 24hour mode
//     BYTE ucMin -> Minute
//     BYTE ucSec -> Second
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetTimestampMode(void* ph, unsigned short* wTimeStampMode);
// Gets the time stamp mode of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wTimeStampMode -> Pointer to a WORD variable to receive the time stamp mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetTimestampMode(void* ph, unsigned short wTimeStampMode);
// Sets the time stamp mode of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wTimeStampMode -> WORD variable to hold the time stamp mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetRecordStopEvent(void* ph, unsigned short* wRecordStopEventMode, unsigned long *dwRecordStopDelayImages);
// Gets the record stop event mode of the camera.
// This option is only available with a pco.1200hs, pco.dimax
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wRecordStopEventMode -> Pointer to a WORD variable to receive the record stop event mode.
//     DWORD* dwRecordStopDelayImages -> Pointer to a DWORD variable to receive the number of images to pass till stop.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetRecordStopEvent(void* ph, unsigned short wRecordStopEventMode, unsigned long dwRecordStopDelayImages);
// Sets the record stop event mode of the camera.
// This option is only available with a pco.1200hs, pco.dimax
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wRecordStopEventMode -> WORD variable to hold the record stop event mode.
//     DWORD dwRecordStopDelayImages -> DWORD variable to hold the number of images to pass till stop.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_StopRecord(void* ph, unsigned short* wReserved0, unsigned long *dwReserved1);
// Activates the Stop according to the settings of PCO_SetRecordStopEvent.
// If you wan't to stop immediately please use PCO_SetRecordingState=0
// This option is only available with a pco.1200hs, pco.dimax
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wReserved0 -> Pointer to a WORD variable (Set content to zero: wReserved0 = 0!).
//     DWORD* dwReserved1 -> Pointer to a DWORD variable (Set to zero!).
// Out: int -> Error message.

/////////////////////////////////////////////////////////////////////
/////// End: Recording commands /////////////////////////////////////
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
/////// Image commands //////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

SC2_SDK_FUNC int WINAPI PCO_GetImageStruct(void* ph, PCO_Image *strImage);
// Gets the image data (= segment data of  all segments).
// see also GetSegmentStruct
// In: HANDLE ph -> Handle to a previously opened camera.
//     PCO_Segment *strImage -> Pointer to a PCO_Image structure to receive the image data.
// Out: int -> Error message.



SC2_SDK_FUNC int WINAPI PCO_GetSegmentStruct(void* ph, unsigned short wSegment, PCO_Segment *strSegment);
// Gets the segment data of the addressed segment. The segment data contains the resolution,
// binning and ROI of the images plus the valid and the maximum image count.
// In: HANDLE ph -> Handle to a previously opened camera.
//     PCO_Segment *strSegment -> Pointer to a PCO_Segment structure to receive the segment data.
// Out: int -> Error message.


SC2_SDK_FUNC int WINAPI PCO_GetSegmentImageSettings(void* ph, unsigned short wSegment,
                                                    unsigned short* wXRes,
                                                    unsigned short* wYRes,
                                                    unsigned short* wBinHorz,
                                                    unsigned short* wBinVert,
                                                    unsigned short* wRoiX0,
                                                    unsigned short* wRoiY0,
                                                    unsigned short* wRoiX1,
                                                    unsigned short* wRoiY1);
// Gets the region of interest of the camera. X0, Y0 start at 1. X1, Y1 end with max. sensor size.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wXRes -> Pointer to a WORD variable to receive the x resolution of the image in segment
//     WORD *wYRes -> Pointer to a WORD variable to receive the y resolution of the image in segment
//     WORD *wBinHorz -> Pointer to a WORD variable to receive the horizontal binning of the image in segment
//     WORD *wBinVert -> Pointer to a WORD variable to receive the vertical binning of the image in segment
//     WORD *wRoiX0 -> Pointer to a WORD variable to receive the left x offset of the image in segment
//     WORD *wRoiY0 -> Pointer to a WORD variable to receive the upper y offset of the image in segment
//     WORD *wRoiX1 -> Pointer to a WORD variable to receive the right x offset of the image in segment
//     WORD *wRoiY1 -> Pointer to a WORD variable to receive the lower y offset of the image in segment
//      x0,y0----------|
//      |     ROI      |
//      ---------------x1,y1
// Out: int -> Error message.




SC2_SDK_FUNC int WINAPI PCO_GetNumberOfImagesInSegment(void* ph, 
                                             unsigned short wSegment,
                                             unsigned long* dwValidImageCnt,
                                             unsigned long* dwMaxImageCnt);
// Gets the number of images in the addressed segment.
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD *dwValidImageCnt -> Pointer to a DWORD varibale to receive the valid image count.
//     DWORD *dwMaxImageCnt -> Pointer to a DWORD varibale to receive the max image count.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetBitAlignment(void* ph, unsigned short* wBitAlignment);
// Gets the bit alignment.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wBitAlignment-> Pointer to a WORD variable to receive the bit alignment.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetBitAlignment(void* ph, unsigned short wBitAlignment);
// Sets the bit alignment.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wBitAlignment-> WORD variable which holds the bit alignment.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_WriteHotPixelList(void* ph, unsigned short wListNo, unsigned short wNumValid,
                                 unsigned short* wHotPixX, unsigned short* wHotPixY);
// Writes a hotpixel list to the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wListNo -> WORD variable which holds the number of the list (zero based).
//     WORD wNumValid -> WORD variable which holds the number of valid members
//     WORD *wHotPixX -> WORD array which holds the x coordinates of a hotpixel list
//     WORD *wHotPixY -> WORD array which holds the y coordinates of a hotpixel list
//     x and y coordinates have to be conistent, that means corresponding coordinate pairs
//     must have the same index!
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_ReadHotPixelList(void* ph, unsigned short wListNo, unsigned short wArraySize, unsigned short* wNumValid, unsigned short* wNumMax,
                                 unsigned short* wHotPixX, unsigned short* wHotPixY);
// Reads a hotpixel list from the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wListNo -> WORD variable which holds the number of the list (zero based).
//     WORD wArraySize -> WORD variable which holds the number of members, which can be transferred
//                        to the list
//     WORD *wNumValid -> Pointer to a WORD variable to receive the number of valid hotpixel.
//     WORD *wNumMax -> Pointer to a WORD variable to receive the max. possible number of hotpixel.
//     WORD *wHotPixX -> WORD array which gets the x coordinates of a hotpixel list
//                       This ptr can be set to ZERO if only the valid and max number
//                       have to be read.
//     WORD *wHotPixY -> WORD array which gets the y coordinates of a hotpixel list
//                       This ptr can be set to ZERO if only the valid and max number
//                       have to be read.
//     x and y coordinates are conistent, that means corresponding coordinate pairs
//     have the same index!
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_ClearHotPixelList(void* ph,
                                              unsigned short wListNo,
                                              unsigned long dwMagic1,
                                              unsigned long dwMagic2);
// Clears a hotpixel list in the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wListNo -> WORD variable which holds the number of the list (zero based).
//     DWORD dwMagic1 -> DWORD variable which holds the unlock code 1.
//     DWORD dwMagic2 -> DWORD variable which holds the unlock code 2.

SC2_SDK_FUNC int WINAPI PCO_GetHotPixelCorrectionMode(void* ph,
                                                      unsigned short *wHotPixelCorrectionMode);
// Sets the time hot pixel correction mode of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wHotPixelCorrectionMode -> Pointer to a WORD variable to receive the hot pixel correction mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetHotPixelCorrectionMode(void* ph,
                                                      unsigned short wHotPixelCorrectionMode);
// Sets the time hot pixel correction mode of the camera.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wHotPixelCorrectionMode -> WORD variable to hold the hot pixel correction mode.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_PlayImagesFromSegmentHDSDI(void* ph,
                                                       unsigned short wSegment,
                                                       unsigned short wInterface,
                                                       unsigned short wMode,
                                                       unsigned short wSpeed,
                                                       unsigned long dwRangeLow,
                                                       unsigned long dwRangeHigh,
                                                       unsigned long dwStartPos);
// Gets the actual play pointer position for the HDSDI interface.
// This option is only available with a pco.dimax
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wSegment -> WORD variable to set play segment (1,2,3,4)
//     WORD wInterface -> WORD variable to set the interface (0x0001 for HDSDI)
//     WORD wMode -> WORD variable to set the play mode
//                   0: Stop play,
//                   1: Fast forward (step 'wSpeed' images),
//                   2: Fast rewind (step 'wSpeed' images), 
//                   3: Slow forward (show each image 'wSpeed'-times)
//                   4: Slow rewind (show each image 'wSpeed'-times)
//                   Additional flags: 0x0100-> 0: Repeat last image
//                                              1: Repeat sequence
//     WORD wSpeed -> WORD variable to set the stepping or repeat count
//     DWORD dwRangeLow -> Lowest image number to be played
//     DWORD dwRangeHigh -> Highest image number to be played
//     DWORD dwStartPos -> Set position to image number #, -1: unchanged
// The first image played will be dwStartPos. In case dwStartPos is -1 the
// play pointer might be out of valid range and will be reset to the most
// recent image (Repeat last image) or to the oldest (Repeat sequence).

SC2_SDK_FUNC int WINAPI PCO_GetPlayPositionHDSDI(void* ph,
                                                 unsigned short   *wStatus,
                                                 unsigned long  *dwPlayPosition);
// Gets the actual play pointer position for the HDSDI interface.
// This option is only available with a pco.dimax
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wStatus -> WORD variable to get the status of image play state machine.
//                      0: no play is active, or play has already stopped
//                      1: play is active, position is valid
//     DWORD *dwPlayPosition -> DWORD variable to get the actual play position

SC2_SDK_FUNC int WINAPI PCO_GetInterfaceOutputFormat(void* ph,
                                                     unsigned short   *wDestInterface,
                                                     unsigned short   *wFormat,
                                                     unsigned short   *wReserved1,
                                                     unsigned short   *wReserved2);
// Gets the output interface settings of cameras with different interfaces.
// This option is only available with a pco.dimax
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD *wDestInterface -> WORD variable to get and set the desired interface.
//                      0: reserved
//                      1: HD/SDI
//                      2: DVI
//     WORD *wFormat -> WORD variable to get the interface format
//                      0: Output is disabled
//                      1: HD/SDI, 1080p25, RGB
//                      2: HD/SDI, 1080p25, arbitrary raw mode
//     WORD *wReserved: Reserved for future use, set *wReserved to zero
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetInterfaceOutputFormat(void* ph,
                                                     unsigned short   wDestInterface,
                                                     unsigned short   wFormat,
                                                     unsigned short   wReserved1,
                                                     unsigned short   wReserved2);
// Sets the output interface settings of cameras with different interfaces.
// This option is only available with a pco.dimax
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wDestInterface -> WORD variable to set the desired interface.
//                      0: reserved
//                      1: HD/SDI
//                      4: DVI
//     WORD wFormat -> WORD variable to set the interface format
//                      0: Output is disabled
//                      1: HD/SDI, 1080p25, RGB
//                      2: HD/SDI, 1080p25, arbitrary raw mode
//     WORD wReserved: Reserved for future use, set wReserved to zero
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetMetaDataMode(void* ph, unsigned short* wMetaDataMode, unsigned short* wMetaDataSize,
                                            unsigned short* wMetaDataVersion);
// This option is only available with pco.dimax
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD* wMetaDataMode -> Pointer to a WORD variable receiving the meta data mode.
//     WORD* wMetaDataSize -> Pointer to a WORD variable receiving the meta data size.
//     WORD* wMetaDataVersion -> Pointer to a WORD variable receiving the meta data version.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetMetaDataMode(void* ph, unsigned short wMetaDataMode, unsigned short* wMetaDataSize,
                                            unsigned short* wMetaDataVersion);
// This option is only available with pco.dimax
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD  wMetaDataMode -> WORD variable to set the meta data mode.
//     WORD* wMetaDataSize -> Pointer to a WORD variable receiving the meta data size.
//     WORD* wMetaDataVersion -> Pointer to a WORD variable receiving the meta data version.
// Out: int -> Error message.

/////////////////////////////////////////////////////////////////////
/////// End: Image commands /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
/////// API Management commands /////////////////////////////////////
/////////////////////////////////////////////////////////////////////

SC2_SDK_FUNC int WINAPI PCO_OpenCamera(void** ph, unsigned short wCamNum);
// Opens a new camera object. Gets the description and sets the date and time.
// In: HANDLE* ph -> Pointer to a handle to receive the camera handle
//     WORD wCamNum -> Current number of the camera, starting with 0.
// Out: int -> Error message.
/* Example:
  void* hCamera;
  ...
  hCamera = NULL;                      // Set to zero in case of openin the first time
  int err = PCO_OpenCamera(&hCamera, 0);
  ...
*/

SC2_SDK_FUNC int WINAPI PCO_OpenCameraEx(void** ph, PCO_OpenStruct* strOpenStruct);
// Opens a new camera object. Gets the description and sets the date and time.
// In: HANDLE* ph -> Pointer to a handle to receive the camera handle
//     PCO_OpenStruct* strOpenStruct -> Structure which contains infos about the opening process
// Out: int -> Error message.
/* Example:
  HANDLE hCamera;
  ...
  hCamera = NULL;                      // Set to zero in case of openin the first time
  PCO_OpenStruct strOpenStruct;
  ...
  strOpenStruct.wSize = sizeof(PCO_OpenStruct);// Sizeof this struct
  strOpenStruct.wInterfaceType = PCO_INTERFACE_FW;
                                       // 1: Firewire, 2: CamLink with Matrox, 3: CamLink with Silicon SW
  strOpenStruct.wCameraNumber = 0;
  //strOpenStruct.wCameraNumAtInterface will be filled by the OpenCameraEx call;
                                       // Current number of camera at the interface
  strOpenStruct.wOpenFlags[0] = InitMode; // Used for setting up camlink with Silicon SW
  // Following defines exist:
  // #define PCO_SC2_CL_ME3_LOAD_SINGLE_AREA 0x0100
  // #define PCO_SC2_CL_ME3_LOAD_DUAL_AREA   0x0200
  // #define PCO_SC2_CL_ME3_LOAD_SINGLE_LINE 0x0300
  // #define PCO_SC2_CL_ME3_LOAD_DUAL_LINE   0x0400 -> this is the default setting

  //strOpenStruct.wOpenFlags[1...19] are not used up to now

  int err = PCO_OpenCamera(&hCamera, &strOpenStruct);
  ...
*/

SC2_SDK_FUNC int WINAPI PCO_CloseCamera(void* ph);
// Closes a camera object.
// In: HANDLE ph -> Handle to a previously opened camera.
// Out: int -> Error message.
/* Example:
  HANDLE hCamera;
  ...
  int err = PCO_OpenCamera(&hCamera, 0);
  ...
  err = PCO_CloseCamera(hCamera);
*/

SC2_SDK_FUNC int WINAPI PCO_AllocateBuffer(void* ph,
                                           short* sBufNr,
                                           unsigned long size,
                                           unsigned short** wBuf,
                                           void** hEvent);
// Allocates an image buffer to receive the image data.
// In: HANDLE ph -> Handle to a previously opened camera.
//     SHORT *sBufNr -> Pointer to a SHORT variable to hold and receive the buffer number.
//                      If a new buffer has to be assigned, set sBufNr to -1.
//                      If an existing buffer should be changed, set sBufNr to the desired nr.
//     DWORD size -> Size of the buffer to be created, or to be changed to.
//     WORD** wBuf -> Pointer to a pointer to a WORD to receive the image data pointer.
//     HANDLE* hEvent -> Pointer to an event handle to receive or to hold an event.
//                       If hEvent set to NULL, a new event will be created and
//                       will be returned through this pointer.
//                       You can create an event handle externally, if you wish, and you can set this
//                       externally created event handle to become this buffer event handle.
// Out: int -> Error message.
/* Example:
  HANDLE hHandleCam;
  SHORT sBufNr;
  WORD *wBuf;                          // wBuf[0...size] represents the image data
  HANDLE hEvent;
  DWORD size, newsize;
  ...
  WORD wXResAct;                       // Actual X Resolution
  WORD wYResAct;                       // Actual Y Resolution
  WORD wXResMax;                       // Maximum X Resolution
  WORD wYResMax;                       // Maximum Y Resolution
  int err = PCO_GetSizes(hCamera, &wXResAct, &wYResAct, &wXResMax, &wYResMax);
  size = wXResMax * wYResMax * sizeof(WORD);
  sBufNr = -1;
  hEvent = NULL;                       // hEvent must be set to either NULL 
  // or if you like to create your own event: hEvent = CreateEvent(0, TRUE, FALSE, NULL);
  // wBuf will receive the pointer to the image data.
  err = PCO_AllocateBuffer(hHandleCam, &sBufNr, size, &wBuf, &hEvent);
  // Get some image here...
  WORD wPixelValuePixel100 = wBuf[100];// Direct access to image data.
  ...
  newsize = wXResAct * wYResAct * sizeof(WORD);// reallocate buffer to a new size.
  err = PCO_AllocateBuffer(hHandleCam, &sBufNr, newsize, &wBuf, NULL);
  ...
*/
SC2_SDK_FUNC int WINAPI PCO_WaitforBuffer(void* ph, int nr_of_buffer, PCO_Buflist *bl, int timeout);
// Waits for one image buffer in bl and returns if one of the buffers is ready. This function is mainly
// used in Linux. In Windows it is implemented for platform independence.
// In: HANDLE ph -> Handle to a previously opened camera.
//     int nr_of_buffer -> number of buffers in PCO_Buflist.
//     PCO_Buflist *bl -> Pointer to a buffer list, which holds the buffers to process.
//     int timeout -> Timeout in milliseconds.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetBuffer(void* ph, short sBufNr, unsigned short** wBuf, void** hEvent);
// Gets the data pointer and the event of a buffer.
// In: HANDLE ph -> Handle to a previously opened camera.
//     SHORT sBufNr -> SHORT variable to hold the buffer number.
//     WORD** wBuf -> Pointer to a pointer to a WORD to receive the image data pointer.
//     HANDLE* hEvent -> Pointer to an event handle to receive or to hold an event.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_FreeBuffer(void* ph, short sBufNr);
// Frees an previously allocated image buffer.
// In: HANDLE ph -> Handle to a previously opened camera.
//     SHORT sBufNr -> SHORT variable to hold the buffer number.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_AddBuffer(void* ph, unsigned long dw1stImage, unsigned long dwLastImage, short sBufNr);
SC2_SDK_FUNC int WINAPI PCO_AddBufferEx(void* ph, unsigned long dw1stImage, unsigned long dwLastImage, short sBufNr,
                                        unsigned short wXRes, unsigned short wYRes, unsigned short wBitPerPixel);
// Adds an image buffer to the driver queue and tries to get the requested images. If the function
// has been done, the event will be fired. This function returns immediately.
// If you've allocated the buffer externally, you have to call the Ex function with the correct sizes.
// This call sets all temporary flags of the buffer status to 0;
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD dw1stImage -> DWORD variable to hold the image number of the first image to be retrieved
//                         This value has to be set to 0, if you are running in preview mode.
//     DWORD dwLastImage -> DWORD variable to hold the image number of the last image to be retrieved
//                         This value has to be set to 0, if you are running in preview mode.
//     SHORT sBufNr -> SHORT variable to hold the buffer number which should be used to get the images.
// InEx: WORD wXRes, WORD wYRes, WORD wBitPerPixel -> Used to calculate the size of the image in RAM
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetBufferStatus(void* ph,
                                            short sBufNr,
                                            unsigned long *dwStatusDll,
                                            unsigned long *dwStatusDrv);
// Gets the status info about the buffer.
// In: HANDLE ph -> Handle to a previously opened camera.
//     SHORT sBufNr -> SHORT variable to hold the number of the buffer to query.
//     DWORD *dwStatusDll -> Pointer to a DWORD variable to receive the status in the SC2_Cam.dll
//                           The status is separated into two groups of flags. 0xFFFF0000 reflect
//                           the static flags and 0x0000FFFF the dynamic flags. The dynamic flags
//                           will be reset by Allocate- and AddBuffer.
//                           0x80000000: Buffer is allocated
//                           0x40000000: Buffer event created internally
//                           0x00008000: Buffer event is set.
//     DWORD *dwStatusDrv -> Pointer to a DWORD variable to receive the status in the driver.
//                           In case of a successful execution this parameter will be set to
//                           PCO_NOERROR (= 0). If an error occurs this parameter will be set
//                           to some PCO_errormessage.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_CancelImages(void* ph);
// Cancels the image processing.
// In: HANDLE ph -> Handle to a previously opened camera.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_RemoveBuffer(void* ph);
// Removes any buffer from the driver queue.
// In: HANDLE ph -> Handle to a previously opened camera.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetImage(void* ph, unsigned short wSegment, unsigned long dw1stImage, unsigned long dwLastImage, short sBufNr);
SC2_SDK_FUNC int WINAPI PCO_GetImageEx(void* ph, unsigned short wSegment, unsigned long dw1stImage, unsigned long dwLastImage, short sBufNr,
                                        unsigned short wXRes, unsigned short wYRes, unsigned short wBitPerPixel);
// Gets images from the camera. The images will be transferred to a previously
// allocated buffer addressed by the sBufNr. This buffer has to be big enough to hold
// all the requested images. This function returns after the images are processed.
// If you've allocated the buffer externally, you have to call the Ex function with the correct sizes.
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD dw1stImage -> DWORD variable to hold the image number of the first image to be retrieved
//     DWORD dwLastImage -> DWORD variable to hold the image number of the last image to be retrieved
//     SHORT sBufNr -> SHORT variable to hold the buffer number which should be used to get the images.
// InEx: WORD wXRes, WORD wYRes, WORD wBitPerPixel -> Used to calculate the size of the image in RAM
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetPendingBuffer(void* ph, int *count);
// Gets the number of buffers which were previously added by PCO_AddBuffer and which are
// left in the driver queue for getting images.
// In: HANDLE ph -> Handle to a previously opened camera.
//     int *count -> Pointer to an int variable to receive the buffer count.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_CheckDeviceAvailability(void* ph, unsigned short wNum);
// Checks whether the device is still available.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wNum -> Current number of the device to check
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetTransferParameter(void* ph, void* buffer, int ilen);
// Sets the transfer parameters for the transfer media
// In: HANDLE ph -> Handle to a previously opened camera.
//     void *buffer -> Pointer to an array to set the transfer parameters.
//     int ilen -> Total length of the buffer in bytes.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetTransferParameter(void* ph, void* buffer, int ilen);
// Gets the transfer parameters for the transfer media
// In: HANDLE ph -> Handle to a previously opened camera.
//     void *buffer -> Pointer to an array to receive the transfer parameters.
//     int ilen -> Total length of the buffer in bytes.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_CamLinkSetImageParameters(void* ph, unsigned short wxres, unsigned short wyres);
// Neccessary while using a CamLink interface
// If there is a change in buffer size (ROI, binning) this function has to be called 
// with the new x and y resolution. Additionally this function has to be called, if you
// switch to another camRAM segment and like to get images.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wxres -> X Resolution of the images to be transferred
//     WORD wyres -> Y Resolution of the images to be transferred
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetTimeouts(void* ph, void *buf_in,unsigned int size_in);
// Here you can set the timeouts for the driver.
// In: HANDLE ph -> Handle to a previously opened camera.
//     void *buffer -> Pointer to an array to set the timeout parameters.
//     int ilen -> Total length of the buffer in bytes.
// [0]: command-timeout,   200ms default, Time to wait while a command is sent.
// [1]: image-timeout,    3000ms default, Time to wait while an image is transferred.
// [2]: transfer-timeout, 1000ms default, Time to wait till the transfer channel expires.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_GetGigEIPAddress(void* ph,
                         unsigned char *BField0, unsigned char *BField1, unsigned char *BField2, unsigned char *BField3);
// Gets the IP address of the camera, e.g. 192.168.1.20
// In: HANDLE ph -> Handle to a previously opened camera.
//     BYTE *BField0 -> Pointer to a BYTE, to receive the upper part of the IP adr., e.g. 192.
//     BYTE *BField1 -> Pointer to a BYTE, to receive the upper mid part of the IP adr., e.g. 168.
//     BYTE *BField2 -> Pointer to a BYTE, to receive the lower mid part of the IP adr., e.g. 1.
//     BYTE *BField3 -> Pointer to a BYTE, to receive the lower part of the IP adr., e.g. 20.
//     WORD size_in -> WORD variable which holds the maximum length of the string.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_SetGigEIPAddress(void* ph, unsigned long dwFlags,
                         unsigned char BField0, unsigned char BField1, unsigned char BField2, unsigned char BField3);
// Gets the IP address of the camera, e.g. 192.168.1.20
// In: HANDLE ph -> Handle to a previously opened camera.
//     DWORD dwFlags -> DWORD flags, to avoid Messagebox set 0x01; others must be zero
//     BYTE BField0 -> BYTE, to set the upper part of the IP adr., e.g. 192.
//     BYTE BField1 -> BYTE, to set the upper mid part of the IP adr., e.g. 168.
//     BYTE BField2 -> BYTE, to set the lower mid part of the IP adr., e.g. 1.
//     BYTE BField3 -> BYTE, to set the lower part of the IP adr., e.g. 20.
//     WORD size_in -> WORD variable which holds the maximum length of the string.
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_AddBufferExtern(void* ph, void* hEvent, unsigned short wActSeg, unsigned long dw1stImage,
                                            unsigned long dwLastImage, unsigned long dwSynch, void* pBuf, unsigned long dwLen, unsigned long *dwStatus);
// Sets an external buffer to the driver. In case of additional metadata, the user has to take care
// for the correct buffer size.
// THE USER HAS TO TAKE CARE WHILE USING THIS FUNCTION CALL, SINCE THE SDK DLL DOES NO PARAMETER CHECKING!
// SETTING INCORRECT DATA MIGHT LEAD TO AN APPCRASH OR BLUESCREEN. PCO ASSUMES NO RESPONSIBILITY!!!
// In: HANDLE ph -> Handle to a previously opened camera.
//     HANDLE hEvent -> Handle to an event, which has to be created externally
//     WORD wActSeg -> WORD to set the segment from which the buffer has to be transferred
//     DWORD dw1stImage -> DWORD variable to hold the image number of the first image to be retrieved
//                         This value has to be set to 0, if you are running in preview mode.
//     DWORD dwLastImage -> DWORD variable to hold the image number of the last image to be retrieved
//                         This value has to be set to 0, if you are running in preview mode.
//     void *pBuf -> Pointer to the buffer (represents the image data)
//     DWORD dwLen -> DWORD to set the length of the image buffer
//     DWORD *dwStatus -> DWORD pointer to get the buffer status (The driver will write the content)
//                        Check this value, after the event is set.
// Out: int -> Error message.


#if defined PCO_METADATA_STRUCT_DEFINED
// Please include sc2_common.h before including sc2_camexport.h in order to enable this function
SC2_SDK_FUNC int WINAPI PCO_GetMetaData(void* ph, short sBufNr,
             PCO_METADATA_STRUCT *pMetaData, unsigned long dwReserved1, unsigned long dwReserved2);
// Gets the image buffer attached meta data, if available
// In: HANDLE ph -> Handle to a previously opened camera.
//     PCO_METADATA_STRUCT *pmeta -> Pointer to a meta data structure.
//     DWORD dwReservedx -> Reserved for future use, set to zero.
#endif

SC2_SDK_FUNC int WINAPI PCO_GetDeviceStatus(void* ph, unsigned short wNum, unsigned long *dwStatus, unsigned short wStatusLen);
// Gets the DeviceAvailability and the Generation count in case of 1394
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wNum -> Current number of the device to check
//     DWORD *dwStatus -> Pointer to an array with at least 1 DWORD
//     WORD wStatusLen -> WORD to hold the number of members in the dwStatus array.
//     dwStatus[0]-> 0x80000000: Device is available (0: not available)
//     dwStatus[1]-> In case of 1394: Generation count (maybe different data with other medias)
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_ControlCommandCall(void* ph,
                         void *buf_in,unsigned int size_in,
                         void *buf_out,unsigned int size_out);
// Issues a low level command to the camera. This call is part of most of the other calls.
// Normally you do not need to call this function. It can be used to cover those camera
// commands, which are not part of this Dll up to now. Please use the other functions while
// their purpose is easier to understand. Furthermore this function is not part of
// the SDK description.

SC2_SDK_FUNC int WINAPI PCO_EnableInterface(unsigned short wInterface, unsigned short wInterfaceEnabled);
// Disables an interface. Set wInterface to the interface which should be disabled.
// Set wInterfaceEnabled to 0.

/////////////////////////////////////////////////////////////////////
/////// End: API Management commands ////////////////////////////////
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
/////// FirmWare commands ///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

SC2_SDK_FUNC int WINAPI PCO_ReadHeadEEProm(void* ph, unsigned short wAddress, unsigned char* bData, unsigned short wLen);
// Reads an EEProm data byte at the requested address.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wAddress -> WORD variable to hold the eeprom address
//     BYTE* bData -> Pointer to a byte variable to receive the eeprom data.
//     WORD wLen -> Length parameter (not used up to now)
// Out: int -> Error message.

SC2_SDK_FUNC int WINAPI PCO_WriteHeadEEProm(void* ph, unsigned short wAddress, unsigned char bData, unsigned short wLen);
// Writes an EEProm data byte to the requested address.
// In: HANDLE ph -> Handle to a previously opened camera.
//     WORD wAddress -> WORD variable to hold the eeprom address
//     BYTE bData -> Byte variable to hold the eeprom data.
//     WORD wLen -> Length parameter (not used up to now)
// Out: int -> Error message.

/////////////////////////////////////////////////////////////////////
/////// End: FirmWare commands //////////////////////////////////////
/////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}       //  Assume C declarations for C++
#endif  //C++
