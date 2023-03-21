#!/bin/bash

echo "Kalyakin Anton 749-1"
echo "Репозитории!"
echo "Программа для просмотра и изменения состояния репозиториев."
echo "Список доступных репозиториев: "
yum repolist all
while true
do
	read -p "Введите имя репозитория: " repo_name
	if yum repolist all | grep -q "^$repo_name"; then
		if yum repolist enabled | grep -q "^$repo_name"; then
			echo "Отключаем репозиторий: "
			yum-config-manager --disable $repo_name 
			yum repolist all
		else
			echo "Подключаем репозиторий: "
			yum-config-manager --enable $repo_name
			yum repolist all
		fi
	else
		echo "Репозиторий $repo_name не найден!" 
	fi
	while true
	do
		echo "Введите "'exit'" для выхода или "'again'" для продолжения: "
		read input
		if [[ $input == "exit" || $input == "again" ]]
		then
		break
		fi
	done
	if [[ $input == "exit" ]]
		then
		break
		fi
done
