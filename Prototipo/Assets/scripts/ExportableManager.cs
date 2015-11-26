using UnityEngine;
using System.Collections;
using System.Reflection;
using System;
using System.IO;
using System.Collections.Generic;

public class ExportableAttribute : Attribute
{
    public ExportableAttribute() { }
}


public class ExportableManager : MonoBehaviour {

    private List<string> toExport;

	// Use this for initialization
	void Start () {
        StreamWriter sw = File.CreateText("pruebaMap.txt");
        sw.WriteLine("Map = {	");
        GameObject[] objects = GameObject.FindObjectsOfType<GameObject>();

        for (int j = 0; j < objects.Length; ++j)
        {
            processObject(objects[j]);
            writeObject(objects[j], sw);
        } // for (int j = 0; j < objects.Length; ++j)

        sw.WriteLine("}");
        sw.Close();
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    private void writeObject(GameObject gameObject, StreamWriter sw)
    {
        if (toExport.Count > 1)
        {
            MeshFilter aux = gameObject.GetComponent<MeshFilter>();
            if (aux != null)
            {
                //TODO: de alguna forma hay que ponerle la ruta completa
                toExport.Add("\t\tmodel = \"" + aux.mesh.name.Substring(0, aux.mesh.name.LastIndexOf("Instance") - 1) + ".mesh\"");
            }
            toExport.Add("\t},");
            for (int w = 0; w < toExport.Count; ++w)
            {
                toExport[w] = toExport[w].Replace('(', '{');
                toExport[w] = toExport[w].Replace(')', '}');

                //toExport[w] = toExport[w].Replace('?', '(');
                //toExport[w] = toExport[w].Replace('¿', ')');
                sw.WriteLine(toExport[w]);
            } //for (int w = 0; w < toExport.Count; ++w)
        } //if (toExport.Count > 1)
    }
    private void processObject(GameObject gameObject)
    {
        toExport = new List<string>();
        string name = gameObject.name;
        if (name.IndexOf('(') > -1)
        {
            name = name.Remove(name.IndexOf('('), 1);
        }
        if (name.IndexOf(')') > -1)
        {
            name = name.Remove(name.IndexOf(')'), 1);
        }
        name = name.Replace(' ', '_');
        name = name.Trim();// (new Char[] { ' ' });
        toExport.Add("\t" + name + " = {	");

        Component[] components = gameObject.GetComponents<Component>();
        for (int z = 0; z < components.Length; ++z)
        {
            processComponent(components[z]);
        }//for (int z = 0; z < components.Length; ++z)
    }
    private void processComponent(Component component)
    {
        FieldInfo[] objectFields = component.GetType().GetFields(BindingFlags.Instance | BindingFlags.Public);

        for (int i = 0; i < objectFields.Length; ++i)
        {
            processField(objectFields[i], component);
        } //for (int i = 0; i < objectFields.Length; ++i)
    }
    private void processField(FieldInfo fielInfo, Component component)
    {
        ExportableAttribute attribute = Attribute.GetCustomAttribute(fielInfo, typeof(ExportableAttribute)) as ExportableAttribute;
        if (attribute != null)
        {
            processAttribute(fielInfo, component);
        } // if (attribute != null)
    }
    private void processAttribute( FieldInfo fielInfo, Component component)
    {
        if (fielInfo.FieldType == typeof(System.String))
        {
            toExport.Add("\t\t" + fielInfo.Name + " = \"" + fielInfo.GetValue(component) + "\",");
        }
        else
        {
            toExport.Add("\t\t" + fielInfo.Name + " = " + fielInfo.GetValue(component) + ",");
        }
    }
}
