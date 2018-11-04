b="aaaa"
file1 = io.open("chainreaction.cc","r")
file2 = io.open("send.cc","w")
contents = file1:read("a")-- read the whole file
file1:close()

delim = '\n\n'.."//"..string.rep("-",70)..'\n\n'
print(delim)
class_pattern = "(class%s*)(%a+[_]*%a*)(%s*%b{};)"
table_class = {}


file3 = io.open("main.h","w")
file3:write("#ifndef main_header\n")
file3:write("#define main_header 1\n\n")
for c,n,con in contents:gmatch(class_pattern) do
  file2 = io.open(n..'.h',"w")
  file3:write("#include \""..n..".h\"\n")
  file2:write("#ifndef "..n.."_header\n")
  file2:write("#define "..n.."_header 1\n\n")
  file2:write("#include \"main.h\"\n\n")
  file2:write(c..n..con)
  file2:write("\n\n#endif")
  file2:close()
end
file3:write("\n#endif")


 classes = {"game_base",
 "player",
 "receive_results",
 "coordinates",
 "box",
 "display_manager",
 "event_manager",
 "animation",
}

for a,b in pairs(classes) do
  patt ="%s*(%a*%s*"..b.."::%a+[%_]*%a*%b().-%b{})"
  file2 = io.open(b..".cc","w")
  file2:write("//"..string.rep('-',20)..' '..b..' '..string.rep('-',20).."\n\n")
  file2:write("\n#include \""..b..".h\"\n\n")
  for w in contents:gmatch(patt) do
    file2:write(w..delim)

  end
end

file4 = io.open("Makefile","a")
file4:write("\n")
objects=""
for a,b in pairs(classes) do
  objects=objects.." "..b..".o "
  file4:write(b..".o: "..b..".h "..b..".cc\n\t")
  file4:write("g++ $(CFLAGS) -c "..b..".cc -o "..b..".o $(LDLIBS)\n\n")
end
--file4:write(objects)
file4:close()

for a,b in pairs(classes)do
  file3:write("class "..b..";\n")
end
file3:close()
