using UnityEngine;
using System.Collections;

public class EventManager {

	public enum EVENTS {
		EVENT_FIREFIGHTER_ON_FIRE,
		EVENT_MAX
	};

    //private static CharacterManager                                 m_charManager;

    // Use this for initialization
    public static void Start () {
       // m_charManager = CharacterManager.hInstance;
    }
	
	/*
	 * Recibe un evento y lo comunica a la clase (por lo general manager) que le corresponda
	 * bReplicable a true lo envia por la red 
	 */
	public static void newEvent(GameEvent hEvent)
	{
		/*switch( hEvent.type )
		{
            case EVENTS.EVENT_FIREFIGHTER_ON_FIRE:
		{
            EventFirefighterOnFire eventFirefighterOnFire = (EventFirefighterOnFire)hEvent;
            //m_charManager.FirefigtherOnFire(eventFirefighterOnFire.m_firefighter);
			break;
		}

		}*/
		//avisar a la red
		/*if ( bReplicable )
		{
			
		}*/
	}
}
