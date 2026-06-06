import { Component, OnInit, ChangeDetectorRef } from '@angular/core';
import { CommonModule } from '@angular/common';
import { timer, switchMap } from 'rxjs';

import { AcessoService } from '../../services/acesso';

@Component({
  selector: 'app-dashboard',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './dashboard.html',
  styleUrls: ['./dashboard.css']
})
export class DashboardComponent implements OnInit {

  acessos: any[] = [];

  constructor(
    private service: AcessoService,
    private cdr: ChangeDetectorRef
  ) {}

  ngOnInit(): void {
    timer(0, 3000)
      .pipe(
        switchMap(() => this.service.listar())
      )
      .subscribe({
        next: (acessos) => {
          this.acessos = acessos;
          this.cdr.detectChanges();
        },
        error: (err) => {
          console.error('Erro ao buscar acessos:', err);
        }
      });
  }
}
