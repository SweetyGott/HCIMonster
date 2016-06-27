package qtestasd;

import java.awt.Event;
import java.awt.FlowLayout;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.DecimalFormat;
import java.util.Random;

import javax.swing.JButton;
import javax.swing.JFrame;

/**
 * @author Kunuk Nykjaer
 */
public class Qlearning {
	final DecimalFormat df = new DecimalFormat("#.##");

	// path finding
	final double alpha = 0.1;
	final double gamma = 0.9;

	// states A,B,C,D,E,F
	// e.g. from A we can go to B or D
	// from C we can only go to C
	// C is goal state, reward 100 when B->C or F->C
	//
	// _______
	// |A|B|C|
	// |_____|
	// |D|E|F|
	// |_____|
	//

	final int stateSmall = 0;
	final int stateMedium = 1;
	final int stateBig = 2;

	final int statesCount = 3;
	final int[] states = new int[] { stateSmall, stateMedium, stateBig };

	// http://en.wikipedia.org/wiki/Q-learning
	// http://people.revoledu.com/kardi/tutorial/ReinforcementLearning/Q-Learning.htm

	// Q(s,a)= Q(s,a) + alpha * (R(s,a) + gamma * Max(next state, all actions) -
	// Q(s,a))

	// int[][] R = new int[statesCount][statesCount]; // reward lookup
	double[][] Q = new double[statesCount][statesCount]; // Q learning

	int[] actionsFromSmall = new int[] { stateSmall, stateMedium, stateBig };
	int[] actionsFromMedium = new int[] { stateSmall, stateMedium, stateBig };
	int[] actionsFromBig = new int[] { stateSmall, stateMedium, stateBig };
	int[][] actions = new int[][] { actionsFromSmall, actionsFromMedium, actionsFromBig };

	String[] stateNames = new String[] { "S", "M", "B" };

	JFrame jf;
	JButton b1;
	JButton b2;
	public Qlearning() {
		init();
		jf = new JFrame();
		b1 = new JButton("B1"){@Override
			public boolean action(Event arg0, Object arg1) {
			// TODO Auto-generated method stub
				pressed(1);
				return true;
		}};
		b2 = new JButton("B2"){@Override
			public boolean mouseDown(Event arg0, int arg1, int arg2) {
			System.out.println("h");return true;}
		};
			
		
		jf.add(b1);
		jf.add(b2);
		jf.show();
		jf.setLayout(new FlowLayout());
		
		setSize(state);
	}

	public void init() {
		/*
		 * R[stateSmall][stateBig] = 100; // from b to c
		 * R[stateMedium][stateBig] = 100; // from f to c R[stateBig][stateBig]
		 * = 100; // from f to c
		 */
	}

	public static void main(String[] args) throws IOException {
		long BEGIN = System.currentTimeMillis();

		Qlearning obj = new Qlearning();
		
		//obj.getNext();
		obj.printResult();
		obj.showPolicy();

		long END = System.currentTimeMillis();
		System.out.println("Time: " + (END - BEGIN) / 1000.0 + " sec.");
	}

	void run() throws IOException {
		/*
		 * 1. Set parameter , and environment reward matrix R 2. Initialize
		 * matrix Q as zero matrix 3. For each episode: Select random initial
		 * state Do while not reach goal state o Select one among all possible
		 * actions for the current state o Using this possible action, consider
		 * to go to the next state o Get maximum Q value of this next state
		 * based on all possible actions o Compute o Set the next state as the
		 * current state
		 */

		// For each episode
		Random rand = new Random();
		for (int i = 0; i < 10; i++) { // train episodes
			// Select random initial state
			int state = rand.nextInt(statesCount);
			/*
			 * while (state != stateBig) // goal state {
			 */
			// Select one among all possible actions for the current state
			int[] actionsFromState = actions[state];

			// Selection strategy is random in this example
			int index = rand.nextInt(actionsFromState.length);
			int action = actionsFromState[index];

			// Action outcome is set to deterministic in this example
			// Transition probability is 1
			int nextState = action; // data structure

			// Using this possible action, consider to go to the next state
			double q = Q(state, action);
			double maxQ = maxQ(nextState);
			// int r = R(state, action);
			int r = 0;
			System.out.println("state: " + nextState);
			if (getNext() == 1)
				r = 100;

			double value = q + alpha * (r + gamma * maxQ - q);
			setQ(state, action, value);

			// Set the next state as the current state
			state = nextState;
			// }
		}
		int state = rand.nextInt(statesCount);
		while (true) // goal state
		{
			// Select one among all possible actions for the current state
			int[] actionsFromState = actions[state];

			// Action outcome is set to deterministic in this example
			// Transition probability is 1
			int nextState = policy(state); // data structure

			// Using this possible action, consider to go to the next state
			double q = Q(state, nextState);
			double maxQ = maxQ(nextState);
			// int r = R(state, action);
			int r = 0;
			setSize(nextState);
			System.out.println("state: " + nextState);
			if (getNext() == 1)
				r = 100;

			double value = q + alpha * (r + gamma * maxQ - q);
			setQ(state, nextState, value);

			// Set the next state as the current state
			state = nextState;
		}

	}

	double maxQ(int s) {
		int[] actionsFromState = actions[s];
		double maxValue = Double.MIN_VALUE;
		for (int i = 0; i < actionsFromState.length; i++) {
			int nextState = actionsFromState[i];
			double value = Q[s][nextState];

			if (value > maxValue)
				maxValue = value;
		}
		return maxValue;
	}

	// get policy from state
	int policy(int state) {
		int[] actionsFromState = actions[state];
		double maxValue = Double.MIN_VALUE;
		int policyGotoState = state; // default goto self if not found
		for (int i = 0; i < actionsFromState.length; i++) {
			int nextState = actionsFromState[i];
			double value = Q[state][nextState];

			if (value > maxValue) {
				maxValue = value;
				policyGotoState = nextState;
			}
		}
		return policyGotoState;
	}

	double Q(int s, int a) {
		return Q[s][a];
	}

	void setQ(int s, int a, double value) {
		Q[s][a] = value;
	}

	/*
	 * int R(int s, int a) { return R[s][a]; }
	 */

	void printResult() {
		System.out.println("Print result");
		for (int i = 0; i < Q.length; i++) {
			System.out.print("out from " + stateNames[i] + ":  ");
			for (int j = 0; j < Q[i].length; j++) {
				System.out.print(df.format(Q[i][j]) + " ");
			}
			System.out.println();
		}
	}

	// policy is maxQ(states)
	void showPolicy() {
		System.out.println("\nshowPolicy");
		for (int i = 0; i < states.length; i++) {
			int from = states[i];
			int to = policy(from);
			System.out.println("from " + stateNames[from] + " goto " + stateNames[to]);
		}
	}

	public void setSize(int val) {
		System.out.println("State: " + val);
		b1.setSize((val+1)*100, 50);
	}

	Random rand = new Random();
	int r = 0;
	int state = rand.nextInt(statesCount);
	int nextState = rand.nextInt(statesCount);
	
	public void pressed(int val) {

		nextState = chooseNext();

		setSize(nextState);
		// Action outcome is set to deterministic in this example
		// Transition probability is 1

		// Using this possible action, consider to go to the next state
		double q = Q(state, nextState);
		double maxQ = maxQ(nextState);
		// int r = R(state, action);
		int r = 0;
		if (val == 1)
			r = 100;

		double value = q + alpha * (r + gamma * maxQ - q);
		setQ(state, nextState, value);

		// Set the next state as the current state
		state = nextState;
	}

	int chooseNext() {
		// Select random initial state
		// int state = rand.nextInt(statesCount);
		// Select one among all possible actions for the current state
		int[] actionsFromState = actions[state];

		// Selection strategy is random in this example
		int nextState;
		if (r < 10) {
			int index = rand.nextInt(actionsFromState.length);
			nextState = actionsFromState[index];
			++r;
		} else {
			nextState = policy(state);
		}
		return nextState;
	}

	public int getNext() throws IOException {
		while (true) {
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

			pressed(Integer.parseInt(br.readLine()));
			// return 0;
		}
	}
}