	SCANLAB RTC 3D Correction File
	==============================

This ct5 correction file is calculated for a SCANLAB 3-axis scan system
for 3D image field correction. The ct5 format succeeds the ctb correction
file format, which is used with the RTC2 to RTC4. For further information
please refer to the RTC manual.


3D Correction File Parameters
-----------------------------

Filename:                     D3_2391.ct5
Program Version:              3.17
Date:                         25.05.2020
Description:                  3D Correction File With F-Theta-Lens
varioSCAN Article Number:     125735
Scanning Lens:                126478
Evaluation Wavelength:        1064 nm

Scan Head Type:               s14          
Scan Angle Calibration:       +/- 11.7 degrees mech.
XY-Swap:                      No

Scan Field Calibration K_xy:  14096 bit/mm
Scan Field Calibration K_z:   881 bit/mm
Max. Field Size (z=0):        74.388 mm
Max. Z-Range:                 +/- 2.3 mm
Max. Field Size (z=max):      74.156 mm
Max. X-/Y-Coordinate Value:   522649 bit

X Stretch-Factor (0 = telecentric):  0.000218
Y Stretch-Factor (0 = telecentric):  -0.0013578
Reference Point:                     (0,0,-0.016) mm
(focus shifter in neutral position)

dl (max. z Control Value +32767):    2.411 mm
dl (min. z Control Value -32767):    -2.446 mm
Max. Scan Angle Mirror 1:            11.208 degrees mech.
Max. Scan Angle Mirror 2:            12.181 degrees mech.

Polynomial Coefficients for Focus Shift Control:
Focus Shift = ds (directed from z=0 opposite to z)
Control Value = A + B*ds*K_z + C*(ds*K_z)^2
A = -215.901
B = 15.3158
C = 5.15874e-005

Polynomial Coefficients for Distortion Correction:
Image Height = f1*theta + f2*theta^2 + f3*theta^3 + f4*theta^4
Scan Angle = theta
f1 = 105.431 mm
f2 = -1.456 mm
f3 = -23.282 mm
f4 = -25.442 mm

