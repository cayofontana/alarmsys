package imp.modelo;

import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPinDigitalOutput;
import com.pi4j.io.gpio.PinState;
import com.pi4j.io.gpio.RaspiPin;


public class Sirene
{
	private boolean status;
	private GpioPinDigitalOutput pinoSirene;

	public Sirene()
	{
		
		status = false;
		pinoSirene = GpioFactory.getInstance().provisionDigitalOutputPin(RaspiPin.GPIO_02);
		pinoSirene.low();
	}

	public void disparar()
	{
		if (!status)
		{
			status = !status;
			pinoSirene.high();
		}
	}

	public void silenciar()
	{
		if (status)
		{
			status = !status;
			pinoSirene.low();
		}
	}
}
