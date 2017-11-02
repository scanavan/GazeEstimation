FOR /L %%A IN (%1, 1, %2) DO (
     start "%%A" /REALTIME "ALLTest\arff_devided_%%A.bat"
)