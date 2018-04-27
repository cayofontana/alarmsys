public class Observador
{
	private Deteccao deteccaoReferencia;

	public Observador()
	{
		deteccaoReferencia = new Deteccao();

		deteccaoReferencia.preencherUltima();
	}

	public Deteccao getDeteccaoReferencia()
	{
		return (deteccaoReferencia);
	}

	public boolean estadoMudou()
	{
		Deteccao deteccao = new Deteccao();
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