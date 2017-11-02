FOR /L %%A IN (1, 1, %1) DO (
     start "%%A" /REALTIME "ALLTest\arff_devided_%%A.bat"
)