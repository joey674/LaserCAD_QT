	SCANLAB RTC 3D Correction File
	==============================

This ct5 correction file is calculated for a SCANLAB 3-axis scan system
for 3D image field correction. The ct5 format succeeds the ctb correction
file format, which is used with the RTC2 to RTC4. For further information
please refer to the RTC manual.


3D Correction File Parameters
-----------------------------

Filename:                     D3_1394.ct5
Program Version:              3.12
Date:                         06.05.2016
Description:                  3D Correction File With F-Theta-Lens
varioSCAN Article Number:     108453
Scanning Lens:                114286
Evaluation Wavelength:        1064 nm

Scan Head Type:               14 mm        
Scan Angle Calibration:       +/- 11.7 degrees mech.
XY-Swap:                      No

Scan Field Calibration K_xy:  14048 bit/mm
Scan Field Calibration K_z:   878 bit/mm
Max. Field Size (z=0):        74.642 mm
Max. Z-Range:                 +/- 2.0 mm
Max. Field Size (z=max):      74.509 mm
Max. X-/Y-Coordinate Value:   523353 bit

X Stretch-Factor (0 = telecentric):  0.00089
Y Stretch-Factor (0 = telecentric):  0.00087
Reference Point:                     (0,0,-0.00834008) mm
(focus shifter in neutral position)

dl (max. z Control Value +32767):    2.180 mm
dl (min. z Control Value -32767):    -2.200 mm
Max. Scan Angle Mirror 1:            11.204 degrees mech.
Max. Scan Angle Mirror 2:            12.175 degrees mech.

Polynomial Coefficients for Focus Shift Control:
Focus Shift = ds (directed from z=0 opposite to z)
Control Value = A + B*ds*K_z + C*(ds*K_z)^2
A = -124.792
B = 17.0417
C = 4.04703e-005

Polynomial Coefficients for Distortion Correction:
Image Height = f1*theta + f2*theta^2 + f3*theta^3 + f4*theta^4
Scan Angle = theta
f1 = 100.101 mm
f2 = -0.235 mm
f3 = -19.475 mm
f4 = -5.159 mm

