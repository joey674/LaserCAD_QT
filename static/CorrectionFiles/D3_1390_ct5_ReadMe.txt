	SCANLAB RTC 3D Correction File
	==============================

This ct5 correction file is calculated for a SCANLAB 3-axis scan system
for 3D image field correction. The ct5 format succeeds the ctb correction
file format, which is used with the RTC2 to RTC4. For further information
please refer to the RTC manual.


3D Correction File Parameters
-----------------------------

Filename:                     D3_1390.ct5
Program Version:              3.12
Date:                         25.04.2016
Description:                  3D Correction File With F-Theta-Lens
varioSCAN Article Number:     125741
Scanning Lens:                120238
Evaluation Wavelength:        355 nm

Scan Head Type:               14 mm        
Scan Angle Calibration:       +/- 11.7 degrees mech.
XY-Swap:                      No

Scan Field Calibration K_xy:  14736 bit/mm
Scan Field Calibration K_z:   921 bit/mm
Max. Field Size (z=0):        71.157 mm
Max. Z-Range:                 +/- 2.0 mm
Max. Field Size (z=max):      71.018 mm
Max. X-/Y-Coordinate Value:   523259 bit

X Stretch-Factor (0 = telecentric):  0.00098
Y Stretch-Factor (0 = telecentric):  0.00073
Reference Point:                     (0,0,-0.0109105) mm
(focus shifter in neutral position)

dl (max. z Control Value +32767):    2.443 mm
dl (min. z Control Value -32767):    -2.476 mm
Max. Scan Angle Mirror 1:            11.211 degrees mech.
Max. Scan Angle Mirror 2:            12.185 degrees mech.

Polynomial Coefficients for Focus Shift Control:
Focus Shift = ds (directed from z=0 opposite to z)
Control Value = A + B*ds*K_z + C*(ds*K_z)^2
A = -145.369
B = 14.4662
C = 4.28443e-005

Polynomial Coefficients for Distortion Correction:
Image Height = f1*theta + f2*theta^2 + f3*theta^3 + f4*theta^4
Scan Angle = theta
f1 = 100.253 mm
f2 = -2.800 mm
f3 = -2.848 mm
f4 = -50.931 mm

