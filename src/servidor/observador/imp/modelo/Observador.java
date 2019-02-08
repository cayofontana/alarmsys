package imp.modelo;

import imp.modelo.persistencia.AcessoDados;

public class Observador
{
	private Deteccao deteccaoReferencia;

	public Observador(AcessoDados acessoDados)
	{
		deteccaoReferencia = new Deteccao(acessoDados);

		deteccaoReferencia.preencherUltima();
	}

	public Deteccao getDeteccaoReferencia()
	{
		return (deteccaoReferencia);
	}

	public boolean estadoMudou(AcessoDados acessoDados)
	{
		Deteccao deteccao = new Deteccao(acessoDados);
		deteccao.preencherUltima();
		
		if (deteccao == null)
			return (false);
		
		if (deteccaoReferencia == null || (deteccao.getId() != deteccaoReferencia.getId()))
		{
			deteccaoReferencia = deteccao;
			return (true);
		}

		return (false);
	}
}