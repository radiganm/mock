---
title: Sum of Two Terms
author: Mac Radigan
header-includes:
 - \usepackage{amsmath}
 - \usepackage{mathrsfs}
 - \usepackage{algorithm}
 - \usepackage{algorithmic}
 - \usepackage{amsfonts}
 - \usepackage{amssymb}
 - \bibliographystyle{IEEEtran}
---
[//]: # sum-two-terms.md
[//]: # Mac Radigan

\newcommand{\slfrac}[2]{\left.#1\middle/#2\right.}
\newcommand{\overbar}[1]{\mkern 1.5mu\overline{\mkern-1.5mu#1\mkern-1.5mu}\mkern 1.5mu}

## Are The Individual Terms Of A Two-Term Sum Present In An Array?

### Overview

Given an array of integers, $\mathbb{X}$, determine whether or not there exist two elements, $m$ and $n$, in the array (at different positions) whose sum is equal to some target value, $\Sigma$.

### Algorithm #1

#### Background

Algorithm 1 makes use of the fact that: 
$$ n = (n-k) + k $$
holds true for any integers $n$ and $k$.

Therefor, given knowledge of the elements present in the sequence $\mathbb{X}$ between 0 and $\Sigma$, we can apply the above formula as a test for existence.

This algorithm makes an assumption about the maximal sum that will be encountered, $M$, and uses this size in allocating a histogram.


#### Implementation

Initially size a histogram of unit bin size based on the expected maximum sum to be supported (say, upper bound $M$).

Build a histogram of unit bin size from the input sequence.

\begin{center}
\begin{equation*}
\begin{split}
h_k 
&= \left| \{ k : k \in \mathbb{X} \} \right| 
\end{split}
\end{equation*}
\end{center}

Scan the histogram up to half the number of bins, applying the formula: $$ n = (n-k) + k $$

If the above euqation holds for any element encountered, then two terms have been found that add to the given sum.

Note that in the implementation we are using the C++ behavior that of integral type having a truth value of T if and only if their register value is non-zero.


#### Performance

  For a sequence xs, having N elements, we have:

|Measure                      |Performance    |
|-----------------------------|--------------:|
| average time complexity     | O(N)          |
| worst case time complexity  | N + 1/2 M     |
------------------------------|----------------
| constant space complexity   | M             |


Note that time complexity assumptions for the average case are not strictly valid without knowledge of the underlying statistical distribution of the input data.


Note that for large $M$, the space complexity of this algorithm may be substantial.  Algorithm 2 provides better performance when $M$ is large.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.C .numberLines}
// ==========================================================================
// has_two_sum_terms (Algorithm 1)
// ==========================================================================
//
//   returns true if there exists elements m and n in sequence xs such that 
//                sum = m + n, where xs and sum are given
//
//   inputs:
//
//     xs : vector<T>   - a sequence of terms to consider
//
//     sum : T          - the specified target sum for testing terms
//
//   template paramters:
//
//     T : class        - the data type of the terms and target sum
//
//     M : size_t       - an upper bound on the expected sum
//     
//   returns:
//
//     has_terms : bool - true  if the input sequence contains two elements
//                              equal to a given sum
//                        false otherwise
// 
// --------------------------------------------------------------------------
template<class T, std::size_t M>
class SequenceCheck
{
 public:
  inline bool has_two_sum_terms(const std::vector<T> &xs, const T sum)
  {
    hist_.fill(0);
    // build a histogram
    for(auto x : xs) if(x<=sum) hist_[x]++;  
    // each element up to half of the histogram
    for(auto k=0; k<std::floor(sum/2.0); ++k)
    {
      // test if n = (n-k) + k
      if( hist_[sum-k] && hist_[k] ) return true; 
    } // k = 0...sum/2
    // special case at N/2 when N even, must have at least two terms
    if( !(sum%2) && hist_[std::floor(sum/2.0)]>1 ) return true;
    return false; // otherwise no such two terms
  } // has_two_terms
 private:
  std::array<T,M> hist_{};
}; // SequenceCheck
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


### Algorithm #2

Note that Algorithm 2 currently does not enforce the selection of two terms in the sequence to be from two distinct different positions.

#### Background

Algorithm 2 makes use of the algebraic group property that every number has an inverse, and thus we may rewrite:

$$
\Sigma = m + n  \leftrightarrow  n = \Sigma - m
$$

Thus for each element $m$ encountered in $\mathbb{X}$, we know uniquely of a corresponding $n$ in $\mathbb{X}$ that we seek.

Therefor, we may scan $\mathbb{X}$ once to identify its compliment with respect to $\Sigma$.

Now, with a set of compliments, say $\overbar{\mathbb{X}} = \Sigma - \mathbb{X}$, we may scan $\mathbb{X}$ again to determine if any element exists in $\overbar{\mathbb{X}}$.

If we find that an element in $\mathbb{X}$ is found in the set of compliments, then we know the sum can be produced from two terms that exist in the sequence.


#### Implementation

Initially an empty, unordered set (uses a hash map implementation).  Call this the compliment set $\overbar{\mathbb{X}}$.

Scan the input sequence, $\mathbb{X}$, for each x in $\mathbb{X}$.  For each $x$, compute the compliment of the sum, $\Sigma$, and $x$, say:  $\overbar{x} = \Sigma - \mathbb{X}$, and insert the compliment $\overbar{x}$ into $\overbar{\mathbb{X}}$.

Scan the input sequence, $\mathbb{X}$, for each $x$ in $\mathbb{X}$ again, checking the compliment set cs for $x$.  If $x$ exists in $\overbar{\mathbb{X}}$, then we have found two terms that produce the sum.

If the end of the sequence is reached without finding a matching x in the compliment set, $\overbar{\mathbb{X}}$, then there are no two terms in $\mathbb{X}$ that will produce the sum.


#### Performance

For a sequence $\mathbb{X}$, having N elements, we have:

|Measure                         |Performance    |
|--------------------------------|--------------:|
| average time complexity        | O(N)          |
| best case time complexity      | N + 1         |
| worst case time complexity     | 2 * N         |
---------------------------------|----------------
| average case space complexity  | O(N)          |
| best  case space complexity    | 1             |
| worst case space complexity    | N             |


Note that the space complexity is dependent only on the number of unique elements in the input sequence ($\mathbb{X}$).


Note that for small M, algorithm 1 can have better worst case time complexity as well as substantially better space complexity.  These assumptions can be further bounded and refined given statistical knowledge of the input data.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.C .numberLines}
// ==========================================================================
// has_two_sum_terms (Algorithm 2)
// ==========================================================================
//
// IMPORTANT:  Note that Algorithm 2 currently does not enforce the selection
//             of two terms in the sequence to be from two distinct different 
//             positions.
//
//   returns true if there exists elements m and n in sequence xs such that 
//                sum = m + n, where xs and sum are given
//
//   inputs:
//
//     xs : vector<T>   - a sequence of terms to consider
//
//     sum : T          - the specified target sum for testing terms
//
//   template paramters:
//
//     T : class        - the data type of the terms and target sum
//
//   returns:
//
//     has_terms : bool - true  if the input sequence contains two elements
//                              equal to a given sum
//                        false otherwise
//
// --------------------------------------------------------------------------
template<class T>
bool has_two_sum_terms(const std::vector<T> &xs, const T sum)
{
  // set of compliments: CS := { c : sum-x=c forall x in xs }
  std::unordered_set<T> compliments;
  for(const auto &x : xs)
  {
    const auto diff = sum - x; // caution: T must be a signed datatype
    compliments.insert(diff);
  } // foreach x in xs
  // scan the input sequence again to identify if any compliments are present
  for(const auto &x : xs)
  {
    if(compliments.find(x) != compliments.end()) return true;
  } // foreach x in xs
  return false;
} // has_two_terms
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


### Source Code
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.C .numberLines}
{% include 'src/sum-two-terms.cc' %}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Test Data Generation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.haskell .numberLines}
{% include 'src/fibonacci.hs' %}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Unit Test Results
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.bash .numberLines}
{% include 'results/sum-two-terms.out' %}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

{# *EOF* #}
