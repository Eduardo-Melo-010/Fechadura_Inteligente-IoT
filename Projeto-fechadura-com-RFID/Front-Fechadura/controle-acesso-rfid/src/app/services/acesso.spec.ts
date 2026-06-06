import { AcessoService } from './acesso';

describe('AcessoService', () => {
  let service: AcessoService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(AcessoService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
