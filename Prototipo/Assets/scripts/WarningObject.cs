using UnityEngine;
using System.Collections;

/*
 * Para que este script funcione, el fuego debe tener colisiones (RigidBody y Collider)
 */
public class WarningObject : MonoBehaviour {

    public string m_Tag = "Fire";

    //marca si se ha activado la alarma alguna vez ya 
    private int numberOfFiresColliding = 0;
    private bool alarmActivated = false;

    public void OnTriggerEnter(Collider other)
    {
        Debug.Log("OTRO");
        if (other.transform.CompareTag(m_Tag))
        {
            Debug.Log("collition ENTER " + numberOfFiresColliding);
            if (numberOfFiresColliding == 0)
            {
                turnAlarmOn();
            }

            numberOfFiresColliding++;          
        }
    }

    public void OnTriggerExit(Collider other)
    {
        if (other.transform.CompareTag(m_Tag))
        {         
            numberOfFiresColliding--;
            if (numberOfFiresColliding == 0)
            {
                turnAlarmOff();
            }
            Debug.Log("collition EXIT " + numberOfFiresColliding);
        }
    }

    /*
     * Activa al alarma. En un principio sólo establece el estado "alarmActivated" e imprime un mensaje
     * En un futuro, puede llamar a un evento que marque la posición, cambie de color... etc.
     */
    private void turnAlarmOn()
    {
        alarmActivated = true;
        Debug.Log("¡WARNING! SE VA A QUEMAR EL " + this.name);
    }

    /*
     * Desactiva la alarma. Lo mismo que el anterior.
     */
    private void turnAlarmOff()
    {
        alarmActivated = false;
        Debug.Log("¡BIEN! Ya no quedan fuegos cerca de " + this.name);
    }
}
