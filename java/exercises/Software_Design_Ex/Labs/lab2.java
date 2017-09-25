import java.io.*;
import java.util.Scanner;

public class lab2{
	// main function that will call other functions
	public static void main(String[] args){
		// input variables
		double Vs, R, C, T;

		// prompt the user to enter values for parameters
		System.out.println("Enter Vs, R, C & T separated by spaces");
		Scanner s = new Scanner(System.in);
		Vs = s.nextDouble();
		R = s.nextDouble();
		C = s.nextDouble();
		T = s.nextDouble();
		s.close();

		// start time, time variables & time incrementation
		double t = 0.00;
		double delT = T/25;
		double time1 = 0.00;
		double time2 = 0.00;

		// display header information
		System.out.println("          " + "Time" + "          " + "Vc");

		// computue values for Vc with incrementing time
		for(int i=0; i<26; i++){
			// display time and Vc(t)
			double vCap = computeVoltage(Vs, R, C, t);
			System.out.println("          " + String.format("%.2f", t) + "          " + String.format("%.2f",vCap));

			// assign values to time1 & time2 if Vc reaches 10% or 90%
			if(vCap >= 0.10 * Vs && time1 == 0.00)
				time1 = t;
			if(vCap >= 0.90 * Vs && time2 == 0.00)
				time2 = t;
			// increment time
			t += delT;
		}
		// calculate rise time
		riseTime(time1, time2);
	}


	// parameters: Vs, R, C, t
	// returns: capacitor voltage (Vc)
	public static double computeVoltage(double Vs, double R, double C, double t){
		double Vc = Vs * (1 - Math.exp(-t/(R*C)));
		return Vc;
	}

	// parameters: time1, time2
	// returns: nothing
	public static void riseTime(double t1, double t2){
		double riseT = t2 - t1;
		if(riseT > 0.00)
			System.out.println("Rise time: " + String.format("%.2f", riseT) + " seconds");
		else
			System.out.println("No rise time available");
	}	
}



