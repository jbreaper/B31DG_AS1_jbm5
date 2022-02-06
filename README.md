### B31DG_AS1_jbm5
# B31DG: Embedded Software
# Assignment 1
###### Jack B. Mavor
###### H00298763



## calculating initial parameters
|Letter|Number|
|:---:|:---:|
|a|1|
|b|2|
|c|3|
|d|4|
|e|5|
|f|6|
|g|7|
|h|8|
|i|9|
|j|10|
|k|11|
|l|12|
|m|13|
|n|13|
|o|12|
|p|11|
|q|10|
|r|9|
|s|8|
|t|7|
|u|6|
|v|5|
|w|4|
|x|3|
|y|2|
|z|1|

|Parameter|Description|Letter|Value|
|:---:|:---:|:---:|:---:|
|a|width of 1^st pulse|M|1300|
|b|width of space between pulses|A|100|
|c|number of pulses per block|V|9|
|d|space between pulse blocks|O|6000|
|mode|secondary system mode|R|2|

|Mode|Effect|
|:---:|:---:|
|1|Remove 3 pulses from pulse block (i.e. c-3 pulses in block) until switch 2 set back to 0.|
|**2**|**Generate inverted form of complete Sig A waveform (from the largest pulse to the shortest) until switch 2 set back to 0**|
|3|insert an extra 3 pulses into pulse block (i.e. c+3 pulses in block) until switch set back to 0|
|4|Half d and b time until switch set back to 0|


![n-s diagram](Signal_Generator.png)
