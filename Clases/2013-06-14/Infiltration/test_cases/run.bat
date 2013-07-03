@ECHO OFF

SET codename=infiltration-

SET id=%1
SET problem=%codename%%id%
SET input=%problem%.in
SET answer=%problem%.ans
SET difference=%problem%.diff
SET output=output.txt
SET elapsed_time=%problem%.time

ptime "..\a < %input% > %output%" > %elapsed_time%
DIFF %output% %answer% > %difference%
DEL %output%