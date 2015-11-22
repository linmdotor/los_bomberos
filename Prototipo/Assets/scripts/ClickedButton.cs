using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class ClickedButton : MonoBehaviour {
    
    public Dropdown m_Equipment;

    private string[] m_EquipmentList = new string[3];
	// Use this for initialization
	void Start () {
        m_EquipmentList[0] = "Axe";
        m_EquipmentList[0] = "HugeEx";
        m_EquipmentList[0] = "FireSuit";
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void PlayerReady()
    {
        GameManager.m_instance.setReadyPlayer(m_Equipment.name);
        GameManager.m_instance.setOptions(m_Equipment.name, m_EquipmentList[m_Equipment.value]);
    }
}
