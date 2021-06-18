# DBF vs QPA (comparativo h(t))
make

echo Conjunto de Tarefas Escalonáveis

echo Impacto no número de tarefas
echo Schedulable &>> ntasks.txt
for pot in {0..4};do
	ntasks=$((10 * (2 ** $pot)))
	echo [Número de tarefas] $ntasks 
	./MAIN.out -n $ntasks -t 1000 -u 0.9 -k 6000 -s 7 -g -c -q &>> ntasks.txt
done

echo Impacto da extensão do período das tarefas 
echo Schedulable &>> tmaxtmin.txt
for pot in {0..4};do
	tmaxtmin=$((10 * (10 ** $pot)))
	echo [Tmax/Tmin] $tmaxtmin 
	./MAIN.out -n 30 -t $tmaxtmin -u 0.9 -k 6000 -s 7 -g -c -q &>> tmaxtmin.txt
done

echo Impacto da utilização 
echo Schedulable &>> utilization.txt
for k in {0..5};do
	utilization=$(echo "0.69+$k*0.06" | bc)
	echo [Utilização] $utilization
	./MAIN.out -n 30 -t 1000 -u $utilization -k 6000 -s 7 -g -c -q &>> utilization.txt
done

echo Conjunto de Tarefas não Escalonáveis

echo Impacto no número de tarefas
echo Unschedulable &>> ntasks.txt
for k in {1..5};do
	ntasks=$((10 * $k))
	echo [Número de tarefas] $ntasks 
	./MAIN.out -n $ntasks -t 1000 -u 0.9 -k 6000 -s 7 -g -q &>> ntasks.txt
done

echo Impacto da extensão do período das tarefas 
echo Unschedulable &>> tmaxtmin.txt
for k in {1..5};do
	tmaxtmin=$((500 * $k))
	echo [Tmax/Tmin] $tmaxtmin 
	./MAIN.out -n 30 -t $tmaxtmin -u 0.9 -k 6000 -s 7 -g -q &>> tmaxtmin.txt
done

echo Impacto da utilização 
echo Unschedulable &>> utilization.txt
for k in {0..5};do
	utilization=$(echo "0.69+$k*0.06" | bc)
	echo [Utilização] $utilization
	./MAIN.out -n 30 -t 1000 -u $utilization -k 6000 -s 7 -g -q &>> utilization.txt
done