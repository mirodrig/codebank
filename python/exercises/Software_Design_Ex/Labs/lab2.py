from math import exp

# parameters: Vs, R, C, t
# returns: capacitor voltage (Vc)
def computeVoltage(Vs, R, C, t):
	Vc = Vs * (1 - exp(-t/(R*C)))
	return Vc

def riseTime(t1, t2):
	riseT = t2 - t1
	if riseT > 0.00:
		print "Rise time: " + str(riseT) + " seconds"
	else:
		print "No rise time available"

def main():
	# declare variables
	Vs = float(raw_input("Value for Vs: "))
	R = float(raw_input("Value for R: "))
	C = float(raw_input("Value for C: "))
	T = float(raw_input("Value for T: "))
	delT = T/25
	t = time1 = time2 = 0.00

	print " " * 15 + "Time" + " " * 15 + "Vc"

	# compute values for Vc with incrementing time
	for i in range(0, 26):
		print " " * 15 + str(round(t, 2)) + " " * 15 + str(round(computeVoltage(Vs, R, C, t), 2))

		# assign values to time1 & time2 when Vc reaches 10% & 90%
		if computeVoltage(Vs, R, C, t) >= 0.10 * Vs and time1 == 0.00:
			time1 = t
		if computeVoltage(Vs, R, C, t) >= 0.90 * Vs and time2 == 0.00:
			time2 = t
		t += delT
	# print rise time
	riseTime(time1, time2)

if __name__ == "__main__":
	main()