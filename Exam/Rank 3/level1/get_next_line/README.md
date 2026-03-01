# GET_NEXT_LINE - EXAM READY 📚

## ✅ Files for exam:

- `get_next_line.c` - Your implementation (51 lines)
- `subject.txt` - Requirements

## 🧠 Quick Memory Guide:

### Core Logic:

```c
1. Read one character at a time: read(fd, &char, 1)
2. Expand buffer: malloc(current_len + 2)
3. Copy old + add new character
4. If '\n' found → return line
5. If EOF → return what we have (or NULL)
```

### Memory Pattern:

```c
temp = malloc(line_len + 2);  // +1 new char, +1 for '\0'
copy old content → add new char → free old → update pointer
```

### Return Cases:

- **'\n' found** → return line immediately
- **EOF + content** → return line
- **EOF + empty** → return NULL
- **Error** → return NULL

## 🎯 Exam Tips:

1. **Test with**: `gcc -D BUFFER_SIZE=42 get_next_line.c main.c`
2. **Remember**: Only `read`, `malloc`, `free` allowed
3. **Key**: Always null-terminate strings
4. **Debug**: Check malloc return values

## 🚀 You're ready! This version is:

- ✅ Simple and fast to write
- ✅ Easy to debug
- ✅ Memory leak safe
- ✅ Handles all edge cases
