
ActiveXCtrl_01ps.dll: dlldata.obj ActiveXCtrl_01_p.obj ActiveXCtrl_01_i.obj
	link /dll /out:ActiveXCtrl_01ps.dll /def:ActiveXCtrl_01ps.def /entry:DllMain dlldata.obj ActiveXCtrl_01_p.obj ActiveXCtrl_01_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ActiveXCtrl_01ps.dll
	@del ActiveXCtrl_01ps.lib
	@del ActiveXCtrl_01ps.exp
	@del dlldata.obj
	@del ActiveXCtrl_01_p.obj
	@del ActiveXCtrl_01_i.obj
