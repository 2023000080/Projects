import sys
try:
  a=float(input("Enter a value:"))
  b=float(input("Enter a value:"))
  operation=input("Enter the operation to perform (+,-,*,/): ")
  result=0
  if operation == '+':
    result=a+b
  elif operation =='-':
    result=a-b
  elif operation =='*':
   result=a*b
  elif operation =='/':
    if b==0:
       raise ZeroDivisionError("Cannot divide by zero")
    result=a/b
  else:
    print("Invalid Input.")
    
    
  print("Result:",result)
except ValueError:
    print("Please enter a valid number.")
except ZeroDivisionError:
    print("Cannot divide by zero.")
