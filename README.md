# Year 01 — Semester 01

> Complete archive of course materials, lab work, assignments, implemented algorithms, and past papers for **Year 1 Semester 1** — University of Colombo School of Computing / Computer Science.

[![Semester](https://img.shields.io/badge/Semester-Y1S1-blue)](#)
[![University](https://img.shields.io/badge/University-UoC-lightgrey)](#)

---

## 📖 Overview

This repository is a centralized collection of all academic resources for **Year 01 Semester 01**. It is intended as a one-stop reference for revision, assignment reference, and interview / exam preparation.

Contents are organized into three main sections:

| Section | Description |
|---|---|
| [`Course Content/`](#-course-content) | Lecture slides, tutorials, labs, assignments, exercises, and textbooks per course |
| [`Important Algorithms/`](#-important-algorithms) | Clean C implementations of core algorithms and data structures |
| [`Past Papers/`](#-past-papers) | Past exam papers from 2020–2025 |

---

## 📚 Courses Covered

| Code | Course | Materials Included |
|---|---|---|
| **ENH 1301** | Application Laboratory | Assignments (01–08), Practicals, Textbooks, Referrals |
| **SCS 1301** | Data Structures and Program Design in C | Exercises (Week 00–07), Labs, Lecture Slides (1–9), Monopoly Project, Textbooks |
| **SCS 1302** | Discrete Mathematics | Lecture Slides (1–8), Assignments, Short Note, Textbook |
| **SCS 1303** | Introduction to Software Engineering | Lecture Slides (1–7), Tutorials (01, 03–07), Textbooks |
| **SCS 1304** | Problem Solving Strategies and Computation Approaches | Lecture Slides (1–7), Labs (01–10), Short Note, Textbook |
| **SCS 1305** | Computer Systems | Lecture Slides (1–8), Tutorials (01–08), Short Note, Textbooks |
| **SCS 1306** | Linear Algebra | Lecture Slides (1–7), Tutorials (01–04), Assignments, Textbooks |
| **SCS 1307** | Probability and Statistics | Lecture Slides (1–10), Assignments, Short Note |

---

## 🗂️ Repository Structure

### High-Level

```
Year_01_Semester_01/
├── Course Content/
├── Important Algorithms/
├── Past Papers/
├── .gitignore
└── README.md
```

### Full File Tree

```
.
├── Course Content/
│   ├── ENH 1301 Application Laboratory/
│   │   ├── Assignments/
│   │   │   ├── Assignment 01/          # 25000799.docx/pdf + Group PDF
│   │   │   ├── Assignment 02/          # part_02 (HTML site) + part_03 (myschool.txt)
│   │   │   ├── Assignment 03/
│   │   │   ├── Assignment 04/
│   │   │   ├── Assignment 06/
│   │   │   ├── Assignment 07/
│   │   │   └── Assignment 08/
│   │   ├── Practicles/                 # Day-02, Day-03, Day-06 & 07, GIT, LaTeX, SSH, Typing & Freeplane
│   │   ├── Refferals/                  # Linux Commands, Ubuntu Cheat Sheet
│   │   └── Textbooks/                  # LaTeX, Linux Fundamentals, The Linux Command Line
│   │
│   ├── SCS 1301 Data Structures and Program Design in C/
│   │   ├── Exercise/
│   │   │   ├── Additional/             # argCheck, matrix, maximum, strCpy, strLen
│   │   │   ├── Week 00/ — Week 07/     # .c programs + PDFs per week
│   │   │   └── Week 05/file_handeling/ # File handling exercises (ex1.c — ex15.c)
│   │   ├── Lab/                        # Lab Sheet 02 + submissions
│   │   ├── Lecture Slides/             # 1 Introduction → 9 Dynamic Memory & Linked Lists
│   │   ├── Monopoly/                   # C Assignment, Mind Map, Property Values.csv
│   │   └── Textbooks/                  # C How to Program, DS Made Easy, CLRS, K&R, etc.
│   │
│   ├── SCS 1302 Discrete Mathematics/
│   │   ├── Assignments/                # Assignment 01, 02 (incl. LaTeX source)
│   │   ├── Lecture Slides/             # 1 Propositional Logic → 8 Number Theory
│   │   ├── Textbooks/                  # Discrete Mathematics and Its Applications
│   │   └── Discrete Maths Short Note.pdf
│   │
│   ├── SCS 1303 Introduction to Software Engineering/
│   │   ├── Lecture Slides/             # 1 Introduction → 7 Testing
│   │   ├── Textbooks/                  # Pressman, Sommerville
│   │   └── Tutorials/
│   │       ├── Tutorial 01/            # C + JS implementations + Flowchart
│   │       └── Tutorial 03 — 07/       # Jira, Trello, Activity Diagrams
│   │
│   ├── SCS 1304 Problem Solving Strategies and Computation Approaches/
│   │   ├── Lab/                        # Lab 01 — Lab 10 (LabSheet + submission)
│   │   ├── Lecture Slides/             # 1 Computational Thinking → 7 Branch and Bound
│   │   ├── Textbooks/                  # Foundations of Algorithms
│   │   └── Problem Solving Short Note.pdf
│   │
│   ├── SCS 1305 Computer Systems/
│   │   ├── Lecture Slides/             # 1 History → 8 Memory Organization
│   │   ├── Textbooks/                  # Org & Architecture, PC Upgrading, etc.
│   │   ├── Tutorials/                  # Tutorial 01 — 08
│   │   └── Computer Systems Short Note.pdf
│   │
│   ├── SCS 1306 Linear Algebra/
│   │   ├── Assignments/                # Assignment 01, 02
│   │   ├── Lecture Slides/             # 1 Introduction → 7 Linear Transformations
│   │   ├── Textbooks/                  # Linear Algebra and Its Applications, etc.
│   │   └── Tutorials/                  # Tutorial 01 — 04
│   │
│   └── SCS 1307 Probability and Statistics/
│       ├── Assignments/                # Assignment 01, 02
│       ├── Lecture Slides/             # 1 Introduction → 10 Discrete Distribution
│       └── Statistics Short Note.pdf
│
├── Important Algorithms/
│   ├── Activity Select Algorithm/       # activty.c + activities_1.txt
│   ├── Data Structures/
│   │   ├── Linked Lists/
│   │   │   ├── Singly Linked Lists/    # singly.c, main.c, types.h
│   │   │   └── Doubly Linked Lists/    # doubly.c, main.c, types.h
│   │   ├── Stack/
│   │   │   ├── Using Arrays/           # stack.c, main.c, types.h
│   │   │   └── Using Linked Lists/     # stack.c, main.c, types.h
│   │   └── Queue/
│   │       ├── Using Arrays/           # queue.c, main.c, types.h
│   │       └── Using Linked Lists/     # queue.c, main.c, types.h
│   ├── Fibonacci/
│   │   ├── fibonacci_recursion.c
│   │   ├── fibonacci_iteration.c
│   │   ├── fibonacci_memoization.c
│   │   └── fibonacci_tabulation.c
│   ├── Searching Algorithms/            # linear, binary, jump + datasets (10 — 100000.txt)
│   │   ├── linear_search.c
│   │   ├── binary_search.c
│   │   └── jump.c
│   ├── Sorting Algorithms/              # bubble, insertion, merge, quick, selection + datasets
│   │   ├── bubble.c
│   │   ├── insertion.c
│   │   ├── merge.c
│   │   ├── quick.c
│   │   └── selection.c
│   └── String Matching/
│       ├── naive_string_matching.c
│       └── dna_1000 — dna_1000000      # benchmark datasets
│
└── Past Papers/
    ├── 2020/   # ENH 1301, SCS 1301, 1302, 1303, 1305
    ├── 2021/   # ENH 1301, SCS 1301, 1302, 1303, 1305
    ├── 2022/   # ENH 1301, SCS 1301, 1302, 1303, 1305
    ├── 2023/   # ENH 1301, SCS 1301, 1302, 1303, 1305
    ├── 2024/   # ENH 1301, 1302, SCS 1301–1307
    └── 2025/   # ENH 1301, 1302, SCS 1301–1307
```
---

## 🔬 Important Algorithms

All implementations are in **C** and located under `Important Algorithms/`. Each folder contains source (`.c`), header (`types.h` where applicable), and a compiled binary for quick testing.

### Build & Run

```bash
# Example: Searching Algorithms
cd "Important Algorithms/Searching Algorithms"
gcc linear_search.c -o linear_search && ./linear_search
gcc binary_search.c -o binary_search && ./binary_search
gcc jump.c -o jump && ./jump

# Sorting
cd "../Sorting Algorithms"
gcc bubble.c -o bubble && ./bubble
gcc quick.c -o quick && ./quick

# Fibonacci variants
cd "../Fibonacci"
gcc fibonacci_recursion.c -o fibonacci_recursion && ./fibonacci_recursion
gcc fibonacci_tabulation.c -o fibonacci_tabulation && ./fibonacci_tabulation

# Data Structures
cd "../Data Structures/Stack/Using Arrays"
gcc main.c stack.c -o stack && ./stack

cd "../../Queue/Using Linked Lists"
gcc main.c queue.c -o queue && ./queue
```

| Category | Algorithms |
|---|---|
| **Searching** | Linear Search, Binary Search, Jump Search |
| **Sorting** | Bubble, Insertion, Selection, Merge, Quick — with datasets `10.txt`–`100000.txt` |
| **Fibonacci** | Recursion, Iteration, Memoization, Tabulation/DP |
| **String Matching** | Naive Matching (with `dna_*` benchmarks) |
| **Greedy** | Activity Selection |
| **Data Structures** | Singly/Doubly Linked List, Stack (Array/Linked List), Queue (Array/Linked List) |

---

## 📝 Past Papers

Exam papers organized by year under `Past Papers/`:

| Year | Available Papers |
|---|---|
| 2020–2023 | ENH 1301, SCS 1301, SCS 1302, SCS 1303, SCS 1305 |
| 2024–2025 | ENH 1301, ENH 1302, SCS 1301, SCS 1302, SCS 1303, SCS 1304, SCS 1305, SCS 1306, SCS 1307 |

Useful for revision — papers are stored as PDFs with original naming (`SCS 1301.pdf`, etc.).

---

## 🚀 Getting Started

```bash
# Clone
git clone https://github.com/ChamalInd/Year_01_Semester_01.git
cd Year_01_Semester_01

# Browse course content
open "Course Content"

# Quick search (example: find all C programs)
find . -name "*.c" | sort
```

No additional dependencies are required to view PDFs/slides. To compile C programs, a standard `gcc` toolchain is sufficient:

```bash
gcc --version   # verify installation (macOS: xcode-select --install, Linux: apt install build-essential)
```

---

## 🤝 Contributing

Contributions are welcome — corrections to short notes, additional past papers, or cleaner algorithm implementations.

1. Fork the repository
2. Create a feature branch (`git checkout -b add/scs1304-lab11`)
3. Commit your changes (`git commit -m "Add SCS1304 Lab 11"`)
4. Push and open a Pull Request

Please keep file naming consistent with existing conventions and avoid committing `.DS_Store` or compiled binaries where not needed.

---

## 📄 License

This repository is for educational purposes. Lecture slides, past papers, and textbooks are property of their respective authors/departments. Original code and notes are shared under the MIT License — see `LICENSE` if present.

---

<p align="center">
  <sub>Year 01 Semester 01 — Compiled with care for revision and reference. Good luck! 🎓</sub>
</p>
