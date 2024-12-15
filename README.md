# 7zip Password Brute Enforcer (not good with naming)
**To use this program, you need to have 7zip installed (or atleast need 7z.exe in the same working directory as the program).**

This progam brute_forces ALL possible passwords for a password-protected file archive until it reaches the correct password.

Though this program can theoretically find the password for any password-protected archive, it scales exponentially for long passwords, meaning that this method isn't really ideal unless you are testing passwords around 5 characters long or less

To use you can type:
```
brute_enforcer.exe "path\to\file.archive" "path\to\output\folder"
```
