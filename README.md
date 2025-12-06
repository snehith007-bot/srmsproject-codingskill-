STUDENT RECORD MANAGEMENT SYSTEM (SRMS)
Project Overview
The Student Record Management System (SRMS) is a C-based console application used to store, update, search, and manage student records.
The project demonstrates file handling, modular programming, sorting, password masking, and role-based access.
Features
Login System
Password masking
Three login attempts
Role-based access
User Roles
Admin: Add, Display, Search, Update, Delete, View Topper
Staff: Add, Display
User: Display, Search, Topper
Guest: Display only
Student Management
Add student
Prevent duplicate roll numbers
Validate marks (0 to 100)
Automatically display students in sorted order
Search student by roll number
Update student
Delete student
Display class topper
Creating Login Credentials
When the program runs for the first time it asks to create credentials.
Credentials are stored in this format:
username password role
Example:
admin admin123 admin
staff staff11 staff
user user22 user
guest guest11 guest
Workflow
User logs in
Role is identified
Menu loads based on role
User performs allowed operations
Data is stored and retrieved from files

User logs out
