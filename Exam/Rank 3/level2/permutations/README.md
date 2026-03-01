# PERMUTATIONS - EXAM READY 🏆

## ✅ Files for exam:
- `permutations.c` - Your winning implementation (40 lines)
- `subject.txt` - Requirements

## 🧠 Quick Memory Guide:

### Core Algorithm - Next Permutation:
```c
1. Sort string first (lexicographically smallest)
2. Find rightmost char smaller than next (pivot)
3. Find smallest char on right > pivot (successor)  
4. Swap pivot and successor
5. Reverse everything after pivot position
6. Repeat until no more permutations
```

### Key Pattern:
```c
do {
    puts(s);                    // Print current permutation
} while (next_perm(s, len));   // Generate next
```

### Next Permutation Steps:
```c
// 1. Find pivot (rightmost decrease)
int i = len - 2;
while (i >= 0 && s[i] >= s[i + 1]) i--;
if (i < 0) return 0;  // Done

// 2. Find successor (smallest > pivot)
int j = len - 1;
while (s[j] <= s[i]) j--;

// 3. Swap pivot and successor
swap(&s[i], &s[j]);

// 4. Reverse suffix
int start = i + 1, end = len - 1;
while (start < end) swap(&s[start++], &s[end--]);
```

## 🎯 Exam Tips:
1. **Start sorted** - Always sort input first
2. **Two-pointer reverse** - Simple and effective
3. **Boundary checks** - Handle edge cases
4. **Memory management** - malloc + free

## 🚀 You're ready! This version is:
- ✅ Only 40 lines - Super fast to write
- ✅ Self-contained - No dependencies  
- ✅ Simple logic - Easy to debug
- ✅ Proven correct - Handles all cases
