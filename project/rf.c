#include <math.h>
//this file holds all the round functions for the game.
//they should all work for numbers in the [0, 1000] range.
//they should output an integer
//they should follow simple rules that can be followed by a human.
//ideally, they should be complicated for a computer to calculate, but easy for a human to recognize

//HELPERS:

unsigned long long power(unsigned long long a, unsigned long long b) {
	unsigned long long i = 0;
	unsigned long long r = 1;
	for (i = 0; i < b; i++) {
		r *= a;
	}
	return r;
}

int getDigitLength(unsigned long long a) {
	int i = 0;
	while (a > 0){
		a = (a - (a % 10))/10;
		i++;
	}
	return i;
}

//END OF HELPERS

//adds the two inputs
unsigned long long add(unsigned long long a, unsigned long long b) {
	return a + b;
}

//literally adds
unsigned long long add_literal(unsigned long long a, unsigned long long b) {
	unsigned long long mult = power(10, getDigitLength(b));
	return (a * mult) + b;
}

//multiplys a by b thrice
unsigned long long multiply3(unsigned long long a, unsigned long long b) {
	return a * b * b * b;
}

//difference
unsigned long long diff(unsigned long long a, unsigned long long b) {
	unsigned long long ma = a;
	unsigned long long mi = b;
	if (a < b) {
		ma = b;
		mi = a;
	}
	return ma - mi;
}

//divide
unsigned long long div1(unsigned long long a, unsigned long long b) {
	return a / b;
}

//mod
unsigned long long mod(unsigned long long a, unsigned long long b) {
	unsigned long long ma = a;
	unsigned long long mi = b;
	if (a < b) {
		ma = b;
		mi = a;
	}
	return ma % mi;
}

//random function
unsigned long long rand1(unsigned long long a, unsigned long long b) {
	return a + 2 * 5 * b + b * 10 + a * 2;
}

//minimum
unsigned long long min1(unsigned long long a, unsigned long long b) {
	unsigned long long mi = b;
	if (a < b) {
		mi = a;
	}
	return mi;
}

//sum of squares
unsigned long long squaresum(unsigned long long a, unsigned long long b) {
	return (a * a) + (b * b);
}

//52,137
unsigned long long fiftytwothousandonehundredthirtyseven(unsigned long long a, unsigned long long b) {
	return 52137;
}

//bx + a, x = 10
unsigned long long lin10(unsigned long long a, unsigned long long b) {
	return (b * 10) + a;
}

//returns a or b depending on which is divisible by the largest number...
unsigned long long candiv(unsigned long long a, unsigned long long b) {
	unsigned long long r = a;
	unsigned long long ma = a;
	if (a < b) {
		ma = b;
	}
	unsigned long long d = ma / 2;
	while (d > 0) {
		if (b % d == 0 && a % d != 0) {
			r = b;
			break;
		}
		d--;
	}
	return r;
}

//greatest common divisor
unsigned long long gcd(unsigned long long a, unsigned long long b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);
}

//hypotenuse
unsigned long long hyp(unsigned long long a, unsigned long long b) {
	return (unsigned long long) sqrt((double)((a * a) + (b * b)));
}

//distance between (a, a) and (b, b)
unsigned long long dist(unsigned long long a, unsigned long long b) {
	return (unsigned long long) sqrt((double)(((b - a) * (b - a)) + ((b - a) * (b - a))));
}

//volume of a bxbx100 cube with a axax100 hole in it (assuming b>a)
unsigned long long cubehole(unsigned long long a, unsigned long long b) {
	unsigned long long ma = a;
	unsigned long long mi = b;
	if (a < b) {
		ma = b;
		mi = a;
	}
	return (ma * ma * ma) - (mi * mi * mi);
}

//volume of a cylinder with a radius and b height
unsigned long long cylinder(unsigned long long a, unsigned long long b) {
	return (unsigned long long) (acos(-1) * a * a * b);
}

//angle of two vectors (ba) (ab)
unsigned long long angle(unsigned long long a, unsigned long long b) {
	unsigned long long v1x = a;
	unsigned long long v1y = b;
	unsigned long long v2x = b;
	unsigned long long v2y = a;
	double a1 = atan2(v1y, v1x) * 180 / 3.141592653589;
	double a2 = atan2(v2y, v2x) * 180 / 3.141592653589;
	if (a2 < a1) {
		double temp = a1;
		a1 = a2;
		a2 = temp;
	}
	return (unsigned long long) a2 - a1;
}

//sum of a geometric and arithmetic series up to a and bth terms
unsigned long long geoarithseries(unsigned long long a, unsigned long long b) {
	unsigned long long c = 1;
	unsigned long long d = 1;
	unsigned long long cs = 0;
	unsigned long long ds = 0;
	int i;
	for (i = 0; i < a; i++) {
		c += 2;
		cs += c;
	}
	for (i = 0; i < b; i++) {
		d *= 2;
		ds += d;
	}
	return cs + ds;
}

//product of the ath and bth term of series
unsigned long long seriesproduct(unsigned long long a, unsigned long long b) {
	unsigned long long c = 5;
	unsigned long long d = 3;
	int i;
	for (i = 0; i < a; i++) {
		c += 2;
	}
	for (i = 0; i < b; i++) {
		d *= 2;
	}
	return c * d;
}

//ath and bth digits of pi
unsigned long long pidig(unsigned long long a, unsigned long long b) {
	unsigned char pi[101] = {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,
								8,3,2,7,9,5,0,2,8,8,4,1,9,7,1,6,9,3,9,9,3,7,5,1,0,
								5,8,2,0,9,7,4,9,4,4,5,9,2,3,0,7,8,1,6,4,0,6,2,8,6,
								2,0,8,9,9,8,6,2,8,0,3,4,8,2,5,3,4,2,1,1,7,0,6,7,9
							};
	a = a % 102;
	b = b % 102;
	unsigned char c = pi[a];
	unsigned char d = pi[b];
	
	return (unsigned long long) (c * 10) + d;
}

//(a + b)th term in fibonacci sequence
unsigned long long fibonacci(unsigned long long a, unsigned long long b) {
	int c = (a + b) % 94;
	if (c == 0){
		return 0;
	} else if (c == 1 || c == 2) {
		return 1;
	}
	int i;
	unsigned long long py1 = 1;
	unsigned long long py2 = 1;
	for (i = 2; i < c; i++)
	{
		unsigned long long temp = py2;
		py2 = py1 + py2;
		py1 = temp;
	}
	return py2;
}

//collatz conjecture
unsigned long long collatz(unsigned long long a, unsigned long long b) {
	unsigned long long count = 0;
	while (count < b) {
		if(a % 2 == 0) {
			a /= 2;
		} else {
			a = (3 * a) + 1;
		}
		count++;
	}
	return a;
}

//how far a ball is thrown given initial velocities
unsigned long long ball(unsigned long long a, unsigned long long b) {
	double vx = (double) a;
	double vy = (double) b;
	double v = sqrt((vx * vx) + (vy * vy));
	double an = atan(vy / vx);
	double r = (v * v) * sin(2 * an) / 9.8;
	return (unsigned long long) r;
}

//given accelleration and final velocity, return distance
unsigned long long acceldist(unsigned long long a, unsigned long long b) {
	double t = (double) b / (double) a;
	double d = (1.0 / 2.0) * (double) a * t * t;
	return (unsigned long long) d;
}

//probability of flipping heads 3/10 times with a weighted coin
unsigned long long coinflip(unsigned long long a, unsigned long long b) {
	double p1 = (double) a / (double) (a + b);
	double p2 = (double) b / (double) (a + b);
	double p_3 = p1 * p1 * p1 * p2 * p2;
	double p_4 = (10 * 9 * 8 * 7 * 6 * 5 * 4) / (3 * 2); 
	return (unsigned long long) (p_4 * p_3 * 10000);
}

//division
unsigned long long div2(unsigned long long a, unsigned long long b) {
	return (unsigned long long) (((double) a / (double) b) * 10000);
}

//sum and round
unsigned long long sumround(unsigned long long a, unsigned long long b) {
	unsigned long long cs = 1;
	unsigned long long i;
	for (i = 1; i <= a; i++) {
		cs += i;
	}
	return cs - (cs % b);
}

//right reimann sum
unsigned long long reimann(unsigned long long a, unsigned long long b) {
	unsigned long long c = 0;
	unsigned long long cs = 0;
	unsigned long long i;
	for (i = 0; i < a; i++) {
		c += b;
		cs += c;
	}
	return cs;
}

//custom function 1
unsigned long long custom1(unsigned long long a, unsigned long long b) {
	unsigned long long r = 1;
	if (a > b) {
		if (a % 3 == 0 || a % 7 == 0) {
			if (a * b > 10000) {
				r = 1;
			} else {
				r = 2;
			}
		} else {
			if (a * b > 20000) {
				r = 3;
			} else {
				r = 4;
			}
		}
	} else {
		if (b % 4 == 0 || b % 9 == 0) {
			if (a + b > 1000) {
				r = 5;
			} else {
				r = 6;
			}
		} else {
			if (a + b > 500) {
				r = 7;
			} else {
				r = 8;
			}
		}
	}
	return r;
}

//custom function 2
unsigned long long custom2(unsigned long long a, unsigned long long b) {
	unsigned long long r = 1;
	if (a > b * 10) {
		if (a > 300 || a < 100) {
			if (b % 6 == 3 || b % 6 == 1) {
				r = 23984;
			} else {
				r = 3957;
			}
		} else {
			if (b > 15) {
				r = 293771;
			} else {
				r = 0;
			}
		}
	} else {
		if (a % 10 == 3 || a % 10 == 9) {
			if (b % 10 == 1 || b % 10 == 2) {
				r = 523489;
			} else {
				r = 620;
			}
		} else {
			if (a % 3 == 1) {
				r = 78998;
			} else {
				r = 82323;
			}
		}
	}
	return r;
}

//custom function 3
unsigned long long custom3(unsigned long long a, unsigned long long b) {
	unsigned long long r = 1;
	if (a % 10 == 2 || a % 10 == 5 || a % 10 == 6) {
		if (b % 10 == 5 || b % 10 == 0) {
			r = 1230943;
		} else {
			r = 2083;
		}
	} else {
		if (b % 10 == 3 || b % 10 == 2 || b % 10 == 1) {
			r = 28245;
		} else {
			r = 343982;
		}
	}
	return r;
}

//counts how many of each digit there is in both numbers, returns a number made with those counts.
unsigned long long digcounts(unsigned long long a, unsigned long long b) {
	unsigned int count[10] = {0,0,0,0,0,0,0,0,0,0};
	unsigned long long cur = 10;
	while (b > 0) {
		unsigned long long i = b % cur;
		b = b - i;
		i = i / (cur / 10);
		count[i]++;
		cur = cur * 10;
	}
	cur = 10;
	while (a > 0) {
		unsigned long long i = a % cur;
		a = a - i;
		i = i / (cur / 10);
		count[i]++;
		cur = cur * 10;
	}
	cur = 0;
	unsigned long long r = 0;
	while (cur < 10) {
		unsigned long long e = 1;
		int j = 0;
		while (j < cur) {
			e *= 10;
			j++;
		}
		r += count[cur] * e;
		cur++;
	}
	return r;
}

//interlaces the digits
unsigned long long interlace(unsigned long long a, unsigned long long b) {
	int lena = getDigitLength(a);
	int lenb = getDigitLength(b);
	int a_digs[lena];
	int b_digs[lenb];
	int i = 0; 
	while (a > 0){
		int cur_dig = (int) a % 10;
		a_digs[i] = cur_dig;
		a = (a - (a % 10)) / 10;
		i++;
	}
	i = 0;
	while (b > 0){
		int cur_dig = (int) b % 10;
		b_digs[i] = cur_dig;
		b = (b - (b % 10)) / 10;
		i++;
	}
	int r_digs[lena + lenb];
	i = 0;
	int i2 = 0; 
	while (i < lena && i < lenb) {
		r_digs[i2] = a_digs[i];
		i2++;
		r_digs[i2] = b_digs[i];
		i2++;
		i++;
	}
	while (i < lena) {
		r_digs[i2] = a_digs[i];
		i2++;
		i++;
	}
	while (i < lenb) {
		r_digs[i2] = b_digs[i];
		i2++;
		i++;
	}
	unsigned long long r = 0;
	for (i = 0; i < lena+lenb; i++) {
		r += r_digs[i] * power(10, i);
	}
	return r;
}

//sum of a regular multiplication table [0, a] x [0, b]
unsigned long long multtablesum(unsigned long long a, unsigned long long b) {
	unsigned long long sum = 0;
	unsigned long long i;
	unsigned long long j;
	for (i = 0; i <= a; i++) {
		for (j = 0; j <= b; j++) {
			sum += i * j;
		}
	}
	return sum;
}

//number of rectangles in a axb grid (M(M+1)(N)(N+1)/4)
unsigned long long rectnum(unsigned long long a, unsigned long long b) {
	return a * (a + 1) * b * (b + 1) / 4;
}

//converts a to base given by b % 10 (0 is 10)
unsigned long long baseconv(unsigned long long a, unsigned long long b) {
	b = b % 10;
	if (b == 0) {
		return a;
	}
	unsigned long long r = 0;
	unsigned long long i = 0;
	while (a > 0) {
		unsigned long long rem = a % b;
		r += rem * power(10, i);
		a = (a - rem) / b;
		i++;
	}
	return r;
}

//converts to binary, makes a multiplication table w/ the digits, returns sum of the ones
unsigned long long binarytablesum(unsigned long long a, unsigned long long b) {
	unsigned long long r = 0;
	while (a > 0) {
		int rema = a % 2;
		a = (a - rema) / 2;
		unsigned long long bt = b;
		while (bt > 0) {
			int remb = bt % 2;
			bt = (bt - remb) / 2;
			r += rema * remb;
		}
	}
	return r;
}

//sort all digits given
unsigned long long digsort(unsigned long long a, unsigned long long b) {
	unsigned int count[10] = {0,0,0,0,0,0,0,0,0,0};
	unsigned long long cur = 10;
	while (b > 0) {
		unsigned long long i = b % cur;
		b = b - i;
		i = i / (cur / 10);
		count[i]++;
		cur = cur * 10;
	}
	cur = 10;
	while (a > 0) {
		unsigned long long i = a % cur;
		a = a - i;
		i = i / (cur / 10);
		count[i]++;
		cur = cur * 10;
	}
	int i;
	unsigned long long cur_dig = 0;
	unsigned long long r = 0;
	for (i = 0; i < 10; i++) {
		unsigned int j;
		for (j = 0; j < count[i]; j++) {
			r = r + (i * power(10, cur_dig));
			cur_dig++;
		}
	}
	return r;
}

//returns sum of digits
unsigned long long digsum(unsigned long long a, unsigned long long b) {
	unsigned int count[10] = {0,0,0,0,0,0,0,0,0,0};
	unsigned long long cur = 10;
	while (b > 0) {
		unsigned long long i = b % cur;
		b = b - i;
		i = i / (cur / 10);
		count[i]++;
		cur = cur * 10;
	}
	cur = 10;
	while (a > 0) {
		unsigned long long i = a % cur;
		a = a - i;
		i = i / (cur / 10);
		count[i]++;
		cur = cur * 10;
	}
	int sum = 0;
	int i;
	for (i = 0; i < 10; i++) {
		sum += count[i] * i;
	}
	return sum;
}

//returns a number whose digits sum to the input digits sum. To decide what number to put, choose the last digit of b, and continue to add 3 to it while mod by 10 to get the digit. If the remaining is <10, just the remaining as the digit.
unsigned long long digsumnum(unsigned long long a, unsigned long long b) {
	unsigned int count[10] = {0,0,0,0,0,0,0,0,0,0};
	unsigned long long cur = 10;
	while (b > 0) {
		unsigned long long i = b % cur;
		b = b - i;
		i = i / (cur / 10);
		count[i]++;
		cur = cur * 10;
	}
	cur = 10;
	while (a > 0) {
		unsigned long long i = a % cur;
		a = a - i;
		i = i / (cur / 10);
		count[i]++;
		cur = cur * 10;
	}
	int sum = 0;
	int i;
	for (i = 0; i < 10; i++) {
		sum += count[i] * i;
	}
	int cur_dig = 1;
	i = 0;
	unsigned long long r = 0;
	while (sum > 0) {
		cur_dig = (cur_dig + 3) % 10;
		if (sum > cur_dig) {
			r += cur_dig * power(10, (unsigned long long) i);
			sum -= cur_dig;
		} else {
			r += sum * power(10, (unsigned long long) i);
			sum = 0;
		}
		i++;
	}
	return r;
}

//reverses the digits
unsigned long long reverse(unsigned long long a, unsigned long long b) {
	unsigned long long ab = (a * power(10, getDigitLength(b))) + b;
	unsigned long long r = 0;
	while (ab > 0) {
		r *= 10;
		r += ab % 10;
		ab = (ab - (ab % 10)) / 10;
	}
	return r;
}

//sum of digits in a, except the length of each "digit" is chosen by (b % 10) % 4
unsigned long long sumvardig(unsigned long long a, unsigned long long b) {
	unsigned int dl = (b % 10) % 4;
	if (dl == 0) {
		return 0;
	}
	unsigned long long dl10 = power(10, dl);
	unsigned long long sum = 0;
	while (a > 0) {
		int i = a % dl10;
		sum += i;
		a = (a - i) / dl10;
	}
	return sum;
}

//returns b/the last digit of a
unsigned long long divdig(unsigned long long a, unsigned long long b) {
	unsigned long long ld = a % 10;
	if (ld == 0) {
		return 0;
	}
	return (b - (b % ld)) / ld;
}

//returns the sum of the last 2 digits of the given even numbers
unsigned long long evensum(unsigned long long a, unsigned long long b) {
	unsigned long long sum = 0;
	if (a % 2 == 0) {
		sum += a % 100;
	}
	if (b % 2 == 0) {
		sum += b % 100;
	}
	return sum;
}

//returns the amount of the second last digit of a is in b
unsigned long long digcount(unsigned long long a, unsigned long long b) {
	unsigned int num = ((a % 100) - (a % 10)) / 10;
	unsigned long long total = 0;
	while (b > 0) {
		unsigned long long i = b % 10;
		b = (b - (b % 10)) / 10;
		if (i == num) {
			total++;
		}
	}
	return total;
}

//multi table, but for every 5 number.
unsigned long long mult5(unsigned long long a, unsigned long long b) {
	unsigned long long i;
	unsigned long long j;
	unsigned long long sum = 0;
	for (i = 0; i <= a; i+=5) {
		for (j = 0; j <= b; j+=5) {
			sum += i * j;
		}
	}
	return sum;
}

//returns a gozinta chain for the product of a and b. (eg: a=2, b=6: 1,2,3,6,12)
unsigned long long gozinta(unsigned long long a, unsigned long long b) {
	unsigned long long num = a * b;
	unsigned long long chain = num;
	unsigned long long i;
	while (num > 1) {
		for (i = (num - (num % 2)) / 2; i > 0; i--) {
			if (num % i == 0) {
				chain += i * power(10, getDigitLength(chain));
				num = i;
				break;
			}
		}
	}
	return chain;
}

//sum of a regular multiplication table [0, a] x [0, b], except addition
unsigned long long addtablesum(unsigned long long a, unsigned long long b) {
	unsigned long long sum = 0;
	unsigned long long i;
	unsigned long long j;
	for (i = 0; i <= a; i++) {
		for (j = 0; j <= b; j++) {
			sum += a + b;
		}
	}
	return sum;
}

//sum of the numbers created by combining the digits of each number.
unsigned long long digpairsum(unsigned long long a, unsigned long long b) {
	unsigned long long sum = 0;
	unsigned long long lda, ldb;
	while (a > 0 && b > 0) {
		lda = a % 10;
		ldb = b % 10;
		sum += (lda * 10) + ldb;
		b = (b - ldb) / 10;
		a = (a - lda) / 10;
	}
	return sum;
}

//a rounded to b
unsigned long long roundb(unsigned long long a, unsigned long long b) {
	return a - (a % b);
}
