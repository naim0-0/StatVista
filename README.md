# StatVista

A C++ data analysis toolkit built for SPL-1

## What it does

StatVista is a terminal-based program that lets you load a CSV file and perform statistical analysis on it — cleaning data, computing statistics, running hypothesis tests, fitting regression models, and plotting charts, all from a menu.

-----

## Project Structure

```
SPL-1/
├── include/       → header files (.h)
├── src/           → source files (.cpp)
└── data/          → CSV and TXT datasets
```

**Source files:**

|File                    |What it does                   |
|------------------------|-------------------------------|
|`utility.cpp`           |Loads and saves CSV files      |
|`exploration.cpp`       |Computes descriptive statistics|
|`preprocessing.cpp`     |Cleans the dataset             |
|`regression.cpp`        |Fits regression models         |
|`hypothesis_testing.cpp`|Runs statistical tests         |
|`plotting.cpp`          |Draws charts in the terminal   |
|`main.cpp`              |Menu system, entry point       |

-----

## How to Compile

Open a terminal inside the `SPL-1/` folder and run:

```powershell
g++ -std=c++17 src\main.cpp src\utility.cpp src\exploration.cpp src\preprocessing.cpp src\regression.cpp src\hypothesis_testing.cpp src\plotting.cpp -I include -o statvista
```

## How to Run

```powershell
.\statvista.exe
```

> Make sure you run it from inside the `SPL-1\` folder — not from inside `src\`.
> If the menu looks garbled, run `chcp 65001` first.

-----

## Features

**Preprocessing**

- Remove null rows
- Replace null values with column mean
- Remove duplicate rows
- Min-Max normalisation
- Z-Score normalisation

**Descriptive Statistics**

- Mean, Median, Mode
- Variance, Standard Deviation
- Min, Max, Q1, Q3, IQR
- Outlier detection (IQR method)
- Pearson Correlation

**Hypothesis Testing**

- Z-Test (one-sided and two-sided)
- T-Test (one-sided and two-sided)
- Chi-Square Test
- Paired T-Test
- One-Way ANOVA

**Regression**

- Simple Linear Regression
- Multiple Linear Regression

**Plotting**

- Bar chart
- Scatter plot

-----

## Data Files

|File                          |Used for                  |
|------------------------------|--------------------------|
|`data/sample.csv`             |Main dataset for analysis |
|`data/oneVariable_dataset.txt`|Z-Test, T-Test, Chi-Square|
|`data/twoVariable_dataset.txt`|Paired T-Test             |
|`data/anova.txt`              |One-Way ANOVA             |
|`data/Z_table.csv`            |Z critical values         |
|`data/T_table.csv`            |T critical values         |
|`data/chi_square_table.csv`   |Chi-square critical values|

When the program asks for a dataset file, type the path like:

```
data/oneVariable_dataset.txt
```

-----

## Built With

- C++17
- No external libraries
- VS Code
- GitHub

-----

**Md Naimul Islam Naim · BSSE 1635 · IIT, University of Dhaka**
**Supervisor: Dr Rezvi Shahariar**
