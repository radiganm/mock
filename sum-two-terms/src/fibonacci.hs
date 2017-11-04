#!/usr/bin/env stack
-- Fibonacci.hs
-- Mac Radigan

fib :: Integer -> Integer
fib 0 = 1
fib 1 = 1
fib n = fib (n-1) + fib (n-2)

main :: IO () 
main = print $ map fib [1..20]

-- *EOF*
