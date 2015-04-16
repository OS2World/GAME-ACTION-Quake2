make build_release
if errorlevel 1 goto end
copy releasei386\quake2.exe ..\..\..
copy releasei386\r_soft.dll ..\..\..
copy releasei386\r_softx.dll ..\..\..
copy releasei386\gameos2.dll ..\..\..\baseq2
copy releasei386\ctf\gameos2.dll ..\..\..\ctf
:end
