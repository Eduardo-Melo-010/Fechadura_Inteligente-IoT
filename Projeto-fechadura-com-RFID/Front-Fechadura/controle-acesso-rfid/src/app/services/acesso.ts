import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable } from 'rxjs';
import { Acesso } from '../models/acesso';
import { environment } from '../../environments/environments';

@Injectable({
  providedIn: 'root'
})
export class AcessoService {

  private url =
    `${environment.supabaseUrl}/rest/v1/acessos?select=*&order=data_hora.desc`;

  constructor(
    private http: HttpClient
  ) {}

  listar(): Observable<Acesso[]> {

    const headers = new HttpHeaders({
      apikey: environment.supabaseKey,
      Authorization: `Bearer ${environment.supabaseKey}`
    });

    return this.http.get<Acesso[]>(
      this.url,
      { headers }
    );
  }
}
