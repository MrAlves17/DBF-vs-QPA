# DBF* vs QPA (frequência do qpa em relação ao DBF*)
make

echo Impacto no número de tarefas
echo ntasks &>> dbf_star_qpa.txt
for pot in {0..4};do
	ntasks=$((10 * (2 ** $pot)))
	echo [Número de tarefas] $ntasks 
	./MAIN.out -n $ntasks -t 1000 -u 0.9 -k 6000 -s 7 -g -b &>> dbf_star_qpa.txt
done

echo Impacto da extensão do período das tarefas 
echo tmaxtmin &>> dbf_star_qpa.txt
for pot in {0..4};do
	tmaxtmin=$((10 * (10 ** $pot)))
	echo [Tmax/Tmin] $tmaxtmin 
	./MAIN.out -n 30 -t $tmaxtmin -u 0.9 -k 6000 -s 7 -g -b &>> dbf_star_qpa.txt
done

echo Impacto da utilização 
echo utilization &>> dbf_star_qpa.txt
for k in {0..5};do
	utilization=$(echo "0.69+$k*0.06" | bc)
	echo [Utilização] $utilization
	./MAIN.out -n 30 -t 1000 -u $utilization -k 6000 -s 7 -g -b &>> dbf_star_qpa.txt
done