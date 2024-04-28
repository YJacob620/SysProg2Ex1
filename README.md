# תכנות מערכות 2 מטלה 1
ת"ז: 322281536

מייל: yairjacob620@gmail.com
## **אופן המימוש והחלוקה בקוד**
הגרף מומש על ידי **מחלקה** `Graph` בעוד שהאלגוריתמים נמצאים ב-**namespace** שנקרא `Algorithms`. שניהם נמצאים ב-namespace בשם `ex1`. דוקומנטציה מפורטת על כל הפונקציות/משתנים נמצאת בקוד עצמו.

בנוסף לקבצים ההכרחיים (`Algorithms.cpp, Algorithms.hpp, Graph.cpp, Graph.hpp`), קיימים גם הקבצים `tests.cpp, main.cpp` המשומשים ליצירת קבצי הרצה, קובץ `makefile` המתאים להם וגם הקובץ `doctest.h` שמשומש לטסטים.
## הרצה של הקוד
דרך טרמינל שנפתח בתיקייה עם כל הקבצים, ניתן להריץ את הפקודות הבאות:

`make` or `make main`

Creates and runs an executable called `main` that runs all of the required 7 functions on a certain graph. 
                        The graph, or rather the adjacency matrix, in main.cpp can be changed to see how it affects the outputs of the functions.

`make tests`

Creates and runs a doctest executable called `tests` that runs dozens of tests on the required 7 functions and prints a tests summary.
