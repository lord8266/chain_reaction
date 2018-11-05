file1 =io.input("display_manager.cc")
file2 =io.output("test.cc")

a=file1:read("a")

b,n=a:gsub("%&boxes(%[%a+[+-]*%a*%])->(%a+)","boxes%1.%2")
print(n)
file2:write(b)
file2:close()
