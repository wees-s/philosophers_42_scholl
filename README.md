<img width="2000" height="1000" alt="image" src="https://github.com/user-attachments/assets/149c6c71-bf0e-47d8-9607-6ec247c908cc" />

---

## Philosophers

### Compilação

```bash
make
```

### Execução

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```

### Parâmetros

* **number_of_philosophers**: quantidade de filósofos
* **time_to_die**: tempo máximo (ms) sem comer
* **time_to_eat**: tempo (ms) que o filósofo passa comendo
* **time_to_sleep**: tempo (ms) que o filósofo passa dormindo
* **number_of_meals** *(opcional)*: quantas vezes cada filósofo deve comer antes do programa encerrar

### Exemplo

```bash
./philo 5 800 200 200 7
```

### Limpeza

```bash
make fclean
```

---
