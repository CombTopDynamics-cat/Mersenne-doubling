# Mersenne-doubling
Study of the primality of Mersenne numbers by calculating periods of the circle doubling map

This repository contains the programs developed in Section 4 and used in Section 5 of the article
*Mersenne numbers and doubling map* by Lluís Alsedà, Antonio Garijo and Xavier Jarque.
It also contains the data and conlusions obtained in Section 5 of the article
(see **Theorem A(a)** and ??????).

Our goal is to calculate the periods of points of the circle of the form *1/q*,
with odd *q*, under the doubling map, and determine when the period is prime
(see **Theorem A(a)** of the article for the motivation). 
In order to increase efficiency, we have separated the calculation of the periods (which is the most critical procedure) from the task (done as post-processing) of determining which of these periods are prime.

The names of the programs used in these two tasks are
**compute_all_periods_in_a_range_of_odd_qs**
and
**IsPrime_geek**.

* **compute_all_periods_in_a_range_of_odd_qs**\
The goal of this program is to compute the periods
of the points of the circle of the form *1/q* under the doubling map,
for each odd *q* in a range of positive integers.
It is a simple and straightforward implementation of the **Algorithm ???** from Section 4.\
**Usage:** compute_all_periods_in_a_range_of_odd_qs.exe q_ini q_end\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
where **q_ini** and **q_end** must be greater than 16.

* **IsPrime_geek**\
Determines the primality of a set of positive integers.
It uses the most naive algorithm, with the help of a
built-in (at compile time) table with the first 49,999,999 prime numbers
(taken from *The PrimePages: prime number research & records* http://https://t5k.org/).
As a consequence, compilation is veeeeeeeery long and tedious, and we must use a special
**gcc** flag. To make it easier, we include the corresponding Makefile and a special '.c'
file (which is already #include'd) with the definition of the prime numbers table.\
**Usage:** IsPrime_geek.exe [-h][--help] file_name field_number\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;where\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
file_name &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;is the full path
to a file containing a column of non-negative integers\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;to be checked for primality.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;The filename must not start with the '-' character.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;Column separators are strings composed of any number of spaces or tabs.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;Lines that start with the character '#' or without a field 'field_number' or with a\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;non-numeric field 'field_number' will be considered comment lines.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
field_number&nbsp;&nbsp;&nbsp;&nbsp;is a positive integer that specifies the number of the column to be read, to check\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;the primality of its elements.

We include four data files with computed periods:
* **EvenPeriodsDataBase_segmented_and_sorted_with_respect_to_Qs.dat.gz**
* **Large_PrimePeriods_segmented_and_sorted.lis.gz**
* **OddPeriods_NotPrime_segmented_and_sorted.lis.gz**
* **PrimePeriods_segmented_and_sorted.lis.gz**

The files have self descriptive filenames. However some clarifications are necessary.
* The three 'sorted.lis' files are sorted with respect to periods.
* Large means that the periods in the file are larger than 136,279,841 which is the number *p* of the last known Mersenne prime in the *List of Known Mersenne Prime Numbers*.
* Segmented refers to the column *segm* in the four files above. When a register has the first field (*segm*) equals to *s*, the number *q*
  in the register verifies *2^(s-1) < q < 2^s*.

A warning: the computation_times are not guaranteed to be completely correct. We are working on recalculating them but, as a computation that is not really necessary, it is too "expensive".

All code in this repository is by Lluís Alsedà, 2026.
