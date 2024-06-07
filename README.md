# Entregable2EDD
Integrantes:
-Sofía López Aguilera (lulunkaii)
-Diego Gutiérrez Mendoza (ElPerroGuaton)

## Caso hashing abierto
Para el hashing abierto se enfrentó un problema al compilar para la experimentación. Se tenía los códigos por separado y al unirlos, no eran compatibles. Por esta razón no se incluye a HashOpen en la compilación por .bat.
Para resolver este problema se adjuntó a un archivo .csv diferente mediante el siguiente código:
HashOpenID hashAbiertoID;
INSERT para UserID:
    for(int i=0; i<21070;i++){

        IdInfo nuevo;

        getline(file,line,',');
        nuevo.university = line;

        getline(file,line,',');
        istringstream os(line);
        os >> nuevo.user_id;

        getline(file,line,',');
        nuevo.user_name = line;

        getline(file,line,',');
        nuevo.number_tweets = stoi(line);

        getline(file,line,',');
        nuevo.friends_count = stoi(line);

        getline(file,line,',');
        nuevo.followers_count = stoi(line);

        getline(file, line, file.widen('\n'));
        nuevo.created_at =line;
        
        auto start = chrono::high_resolution_clock::now();
        //####################INICIO DEL CLOCK####################
        
        hashAbiertoID.put(nuevo.user_id,nuevo); 

        //#####################FIN DEL CLOCK######################
        auto end = chrono::high_resolution_clock::now();

        double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        running_time *= 1e-9;

        suma += running_time;

    }
    resultados<<i+1<<";universities_followers.csv;hashing_abierto_insert;"<<21070<<";"<<suma<<'\n';

Este código se repetía la misma cantidad de veces que las anteriores experimentadas para simular lo que hacía el .bat. Para poder conseguir las de Username se hace lo mismo pero cambiando la última línea por hashAbiertoUsername.put(nuevo.user_name, nuevo).
Se hizo lo mismo para las búsquedas:

SEARCH not found Username:
for(int i=0; i<20;i++)
    {
        file.clear();
        file.seekg(0);

        getline(file,line);

        double suma = 0;

        for(int i=0; i<21070;i++){

            UserInfo nuevo;

            getline(file,line,',');
            nuevo.university = line;

            getline(file,line,',');
            istringstream os(line);
            os >> nuevo.user_id;

            getline(file,line,',');
            nuevo.user_name = line;

            getline(file,line,',');
            nuevo.number_tweets = stoi(line);

            getline(file,line,',');
            nuevo.friends_count = stoi(line);

            getline(file,line,',');
            nuevo.followers_count = stoi(line);

            getline(file, line, file.widen('\n'));
            nuevo.created_at =line;

            auto start = chrono::high_resolution_clock::now();
            //####################INICIO DEL CLOCK####################

            hashAbiertoUsername.search(to_string(i));

            //#####################FIN DEL CLOCK######################
            auto end = chrono::high_resolution_clock::now();

            double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

            running_time *= 1e-9;

            suma += running_time;
        }

        resultados<<i+1<<";universities_followers.csv;hashing_abierto_search_NOT_found_OpenHashUsername;"<<21070<<";"<<suma<<'\n';

    }

SEARCH FOUND Username

for(int i=0; i<20;i++)
    {
        file.clear();
        file.seekg(0);

        getline(file,line);

        double suma = 0;

        for(int i=0; i<21070;i++){

            UserInfo nuevo;

            getline(file,line,',');
            nuevo.university = line;

            getline(file,line,',');
            istringstream os(line);
            os >> nuevo.user_id;

            getline(file,line,',');
            nuevo.user_name = line;

            getline(file,line,',');
            nuevo.number_tweets = stoi(line);

            getline(file,line,',');
            nuevo.friends_count = stoi(line);

            getline(file,line,',');
            nuevo.followers_count = stoi(line);

            getline(file, line, file.widen('\n'));
            nuevo.created_at =line;

            auto start = chrono::high_resolution_clock::now();
            //####################INICIO DEL CLOCK####################

            hashAbiertoUsername.search(nuevo.user_name);

            //#####################FIN DEL CLOCK######################
            auto end = chrono::high_resolution_clock::now();

            double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

            running_time *= 1e-9;

            suma += running_time;
        }

        resultados<<i+1<<";universities_followers.csv;hashing_abierto_search_found_OpenHashUsername;"<<21070<<";"<<suma<<'\n';

    }
