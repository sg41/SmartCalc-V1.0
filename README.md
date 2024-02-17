# SmartCalc v1.0 Program Description

## Overview
SmartCalc v1.0 is a C program developed using the C11 standard with the gcc compiler. This calculator project follows structured programming principles, adheres to the Google coding style, and integrates GUI interfaces implemented with GTK+ library.

## Key Features

### 1. Historical Background
- Provides insights into the history of calculators, starting from ancient prototypes to modern electronic devices.
- Discusses the evolution of calculators, including the development of integrated circuits, programmable calculators, and the transition to pocket-sized devices.

### 2. Polish Notation and Reverse Polish Notation
- Explores the origins of prefix (Polish) notation and reverse Polish (RPN) notation.
- Highlights the advantages of RPN, its usage in programming languages, and its popularity among scientists and engineers.

### 3. Dijkstra's Algorithm (Shunting-yard Algorithm)
- Explains Edsger Dijkstra's algorithm for converting infix expressions to reverse Polish notation.
- Describes the implementation steps of the shunting-yard algorithm using stacks and tokens.

## Chapter I

### Introduction
- Outlines the project's goal to implement an extended calculator in the C programming language.
- Describes the calculator's functionalities, including basic arithmetic operations, mathematical functions, and support for variable 'x' in expressions.
- Mentions additional features like credit and deposit calculators.

## Chapter II

### Information
- Provides historical background on the development of calculators, emphasizing key milestones.
- Explores the etymology of the word "calculator" and its roots in counting with pebbles.
- Introduces the concepts of Polish notation and reverse Polish notation, along with their historical significance.
- Discusses Dijkstra's algorithm for expression conversion.

## Chapter III

### Part 1. Implementation of SmartCalc v1.0
- Specifies the development requirements for SmartCalc v1.0, including the use of C11, gcc compiler, and GUI libraries.
- Emphasizes adherence to the Google coding style and the implementation of the MVC pattern.
- Describes the features of SmartCalc v1.0, such as input support for integers and real numbers, expression calculation, graph plotting, and limited domain/codomain.

### Part 2. Bonus. Credit Calculator
- Introduces a credit calculator mode for calculating credit-related parameters.
- Defines inputs (total credit amount, term, interest rate, type) and outputs (monthly payment, overpayment, total payment).

### Part 3. Bonus. Deposit Calculator
- Presents a deposit profitability calculator mode.
- Specifies inputs (deposit amount, term, interest rate, tax rate, periodicity of payments, etc.) and outputs (accrued interest, tax amount, final deposit amount).

## How to Make

### Step 1: Clone the Repository
```bash
git clone https://github.com/sg41/SmartCalc-V1.0.git SmartCalc
cd SmartCalc
make install
```
