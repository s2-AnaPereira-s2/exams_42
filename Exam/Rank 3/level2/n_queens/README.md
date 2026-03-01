# N-QUEENS - EXAM READY 🏆

## ✅ Files for exam:
- `n_queens.c` - Your winning implementation (47 lines)
- `subject.txt` - Requirements

## 🧠 Quick Memory Guide:

### Core Algorithm - Backtracking:
```c
1. Try placing queen in each row of current column
2. Check if placement is safe (no conflicts)
3. If safe: place queen and recurse to next column
4. If reached last column: print solution
5. Backtrack and try next position
```

### Safety Check (3 conditions):
```c
for (int i = 0; i < col; i++) {
    if (board[i] == row ||              // Same row
        board[i] - row == i - col ||    // Diagonal ↗ 
        board[i] - row == col - i)      // Diagonal ↘
        return 0;  // Not safe
}
return 1;  // Safe
```

### Key Functions:
1. **is_safe()** - Check if queen placement is valid
2. **solve()** - Recursive backtracking solver  
3. **main()** - Setup board and start solving

## 🎯 Exam Tips:
1. **Board representation**: `board[col] = row`
2. **Diagonal formulas**: Key to remember the math
3. **Base case**: `if (col == n)` → print solution
4. **Backtracking**: Try all rows, recurse, return

## 🚀 You're ready!
- ✅ 47 lines only - Fast to write
- ✅ Self-contained - No dependencies
- ✅ Simple logic - Easy to debug
- ✅ Tested and working - Handles all cases
